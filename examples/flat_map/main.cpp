#include <actor-zeta/flat_map.hpp>

#include <vector>

#include <unordered_map>
#include <cassert>

void test_ctors() {
  {
    //test sizes
    flat_map<int, std::string> fmap;
    std::unordered_map<int, std::string> map;

    assert(fmap.size() == 0);
    assert(map.size() == 0);

    fmap.insert(std::pair<int, std::string>(0, "0"));
    map.insert(std::pair<int, std::string>(0, "0"));

    assert(fmap.size() == 1);
    assert(map.size() == 1);
  }
  {
    //ctor via initialization list
    flat_map<int, std::string> fmap          { {0, "0"}, {1, "1"} };
    std::unordered_map<int, std::string> map { {0, "0"}, {1, "1"} };

    assert(fmap.size() == map.size());
    assert(fmap.begin()->first == 0 && map.begin()->first == 0);
    assert((fmap.begin() + 1)->first == 1 && (fmap.begin() + 1)->first == 1);
    assert(fmap.begin()->second == "0" && map.begin()->second == "0");
    assert((fmap.begin() + 1)->second == "1" && (fmap.begin()+ 1)->second == "1");
  }
  {
    //ctor via copy ctor
    flat_map<int, std::string> fmap          { {0, "0"}, {1, "1"} };
    std::unordered_map<int, std::string> map { {0, "0"}, {1, "1"} };
    flat_map<int, std::string> fmap2(fmap);
    std::unordered_map<int, std::string> map2(map);

    assert(fmap.size() == map.size());
    assert(fmap.begin()->first == 0 && map.begin()->first == 0);
    assert((fmap.begin() + 1)->first == 1 && (fmap.begin() + 1)->first == 1);
    assert(fmap.begin()->second == "0" && map.begin()->second == "0");
    assert((fmap.begin() + 1)->second == "1" && (fmap.begin()+ 1)->second == "1");
  }
  {
    //ctor via iterator range
    flat_map<int, std::string> fmap          { {0, "0"}, {1, "1"} };
    std::unordered_map<int, std::string> map { {0, "0"}, {1, "1"} };
    flat_map<int, std::string> fmap2(fmap.begin(), fmap.end());
    std::unordered_map<int, std::string> map2(map.begin(), map.end());

    assert(fmap.size() == map.size());
    assert(fmap.begin()->first == 0 && map.begin()->first == 0);
    assert((fmap.begin() + 1)->first == 1 && (fmap.begin() + 1)->first == 1);
    assert(fmap.begin()->second == "0" && map.begin()->second == "0");
    assert((fmap.begin() + 1)->second == "1" && (fmap.begin()+ 1)->second == "1");
  }
}

void test_insert() {
  {
    //test if pair is already inserted
    flat_map<int, std::string> fmap;
    std::unordered_map<int, std::string> map;
    
    assert(map.insert( {0, "0"} ).second == fmap.insert( {0, "0"} ).second); //true
    assert(map.insert( {0, "0"} ).second == fmap.insert( {0, "0"} ).second); //false
  }
}

int main() {
  test_ctors();
  test_insert();

  return 0;
}
