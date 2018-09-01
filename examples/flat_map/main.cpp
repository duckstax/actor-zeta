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

void test_emplace() {
  { //test if we can emplace elements
    flat_map<int, std::string> fmap;
    fmap.emplace( 0, "0" );
    std::unordered_map<int, std::string> map;
    map.emplace( 0, "0" );
    
    assert(fmap.size() == 1);
    assert(map.size() == 1);
  }
}

void test_swap() {
  { //test if contents swapped
    flat_map<int, std::string> fmap;
    
    fmap.emplace( 0, "0" );
    fmap.emplace( 1, "1" );
    fmap.emplace( 2, "2" );
    fmap.emplace( 3, "3" );
    
    flat_map<int, std::string> fmap_2;
    fmap_2.emplace( 4, "4" );
    fmap_2.emplace( 5, "5" );
    fmap_2.emplace( 6, "7" );
    
    fmap_2.swap( fmap );
    
    assert( fmap.size() == 3 );
    assert( fmap_2.size() == 4 );
  }
}

void test_at() {
  {
    flat_map<int, std::string> fmap;
    fmap.emplace( 0, "0" );

    const std::string val = fmap.at( 0 );
    assert( val == "0" );
  }
  {
    std::unordered_map<int, std::string> map;
    map.emplace( 0, "0" );

    const std::string val = map.at( 0 );
    assert( val == "0" );
  }
}

int main() {
  test_ctors();
  test_insert();
  test_emplace();
  test_swap();
  test_at();

  return 0;
}
