#include "./http_stuff.h"
#include "./json.hpp"
#include "./helpers/algorithms.hpp"
#include "./helpers/snakelib.hpp"
#include <iostream>
using namespace std;
using namespace nlohmann;

string algorithmName = "dog";

void add_cors_headers(httplib::Response &res) {
  res.set_header("Allow", "GET, POST");
  res.set_header("Access-Control-Allow-Origin", "*");
  res.set_header("Access-Control-Allow-Methods", "GET, POST");
  res.set_header("Access-Control-ALlow-Headers", "Content-Type");
}

Point makePoint(const json data){
  Point newPoint {};
  newPoint.x = data["x"];
  newPoint.y = data["y"];
  return newPoint;
}

Snake makeSnake(const json data){
  Snake newSnake {};
  newSnake.id = data["id"];
  newSnake.health = data["health"];
  auto body = data["body"];
  for(const auto &bodyPoint : body){
    Point newPoint = makePoint(bodyPoint);
    newSnake.parts.push_back(newPoint);
  }
  newSnake.dead = false;
  return newSnake;
}

World makeWorld(const json data){
  World world {};
  world.id = data["game"]["id"] ;
  auto foods = data["board"]["food"];
  for(const auto &food : foods){
    Point newFood = makePoint(food);
    world.food.push_back(newFood);
  }
  auto snakes = data["board"]["snakes"];
  for(const auto &snake : snakes){
    Snake newSnake = makeSnake(snake);
    world.snakes.push_back(newSnake);
  }
  world.height = data["board"]["height"];
  world.width = data["board"]["width"];
  world.you = data["you"]["id"];
  return world;
}

int main(void) {
  httplib::Server svr;

  svr.Options(".*", [](const auto &, auto &res) {
    res.set_content("ok", "text/plain");
    add_cors_headers(res);
  });
  svr.Get("/", [](const auto &, auto &res) {
    string head = "all-seeing";    // TODO: Change head
    string tail = "curled";        // TODO: Change tail
    string author = "killer-team"; // TODO: Change your battlesnake username
    string color = "#F00100";      // TODO: Change a hex color
    res.set_content("{\"apiversion\":\"1\", \"head\":\"" + head +
                        "\", \"tail\":\"" + tail + "\", \"color\":\"" + color +
                        "\", " + "\"author\":\"" + author + "\"}",
                    "application/json");

    add_cors_headers(res);
  });
  svr.Post("/end", [](const auto &, auto &res) {
    res.set_content("ok", "text/plain");
    add_cors_headers(res);
  });
  svr.Post("/start", [](const auto &req, auto &res) mutable {
    const json data = json::parse(req.body);
    auto algo = Algorithms::get(algorithmName);
    string gameId = data["you"]["id"];
    algo->start(gameId);
    res.set_content("ok", "text/plain");
    add_cors_headers(res);
  });
  svr.Post("/move", [](auto &req, auto &res) mutable {
    const json data = json::parse(req.body);
    auto algo = Algorithms::get(algorithmName);
    World world = makeWorld(data);
    GameState state(world);
    Direction direction = algo->move(state);
    std::string directionStr = directionToString(direction);
    world.prettyPrint();
    // string directionStr = "down";
    res.set_content("{\"move\": \"" + directionStr + "\"}", "text/plain");

    add_cors_headers(res);
  });
  svr.listen("0.0.0.0", 8080);
  cout << "Server started";
}