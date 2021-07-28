#include <iostream>
#include <forward_list>
#include <string>

class Animal {
 private:
  std::string type;
 public:
  Animal(): type() { };
  Animal(const std::string& animal_type): type(animal_type) { };
  std::string get_type() { return type; }
};

class AnimalShelter {
 private:
  std::forward_list<Animal> animal_queue;
  void DequeueType(const std::string& type); // auxiliary function to avoid copy paste
 public:
  AnimalShelter(): animal_queue() { };
  void Enqueue(const std::string& type);
  void DequeueAny();
  void DequeueDog();
  void DequeueCat();
  void Print(); // debug function
};

/*
  Time: O(n)
*/
void AnimalShelter::DequeueType(const std::string& type) {
  if (!animal_queue.empty()) {
    std::forward_list<Animal>::iterator remove_it;
    bool found = false;

    for (auto it = animal_queue.before_begin(); it != animal_queue.end(); it++) {
      auto next_it = it;
      next_it++;

      if (next_it != animal_queue.end() && next_it->get_type() == type) {
        found = true;
        remove_it = it;
      }
    }
    
    if (found)
      animal_queue.erase_after(remove_it);
  }
}

void AnimalShelter::Enqueue(const std::string& type) {
  class Animal new_animal = Animal(type);
  animal_queue.push_front(new_animal);
}

/*
  Time: O(n)
*/
void AnimalShelter::DequeueAny() {
  if (!animal_queue.empty()) {
    std::forward_list<Animal>::iterator remove_it, next_it;
    
    for (auto it = animal_queue.before_begin(); it != animal_queue.end(); it++) {
      next_it = it;
      next_it++;
      next_it++;

      if (next_it == animal_queue.end()){
        remove_it = it;
        break;
      }
    }
    animal_queue.erase_after(remove_it);
  }
}

void AnimalShelter::DequeueCat() {
  std::string cat_type("cat");
  DequeueType(cat_type);
}

void AnimalShelter::DequeueDog() {
  std::string dog_type("dog");
  DequeueType(dog_type);
}

void AnimalShelter::Print() {
  for (auto & animal : animal_queue) {
    std::cout << animal.get_type() << " "; 
  }
  std::cout << std::endl;
}

int main() { 
  class AnimalShelter my_shelter;
  std::string dog_type("dog");
  std::string cat_type("cat");

  my_shelter.Enqueue(dog_type);
  my_shelter.Enqueue(cat_type);
  my_shelter.Enqueue(dog_type);
  my_shelter.Enqueue(dog_type);
  my_shelter.Print(); // ok, end --> dog dog cat dog <-- begin
  my_shelter.DequeueDog();
  my_shelter.Print(); // ok, end --> dog dog cat <-- begin
  my_shelter.DequeueDog();
  my_shelter.Print(); // ok, end --> dog cat <-- begin

  my_shelter.Enqueue(cat_type);
  my_shelter.Enqueue(dog_type);
  my_shelter.Enqueue(dog_type);
  my_shelter.DequeueCat();
  my_shelter.Print(); // ok, end --> dog dog cat dog <-- begin
  my_shelter.DequeueCat();
  my_shelter.Print(); // ok, end --> dog dog dog <-- begin
  my_shelter.DequeueAny();
  my_shelter.Print(); // ok, end --> dog dog <-- begin 
  my_shelter.DequeueAny();
  my_shelter.DequeueAny();
  my_shelter.Print(); // ok, empty

  my_shelter.Enqueue(dog_type);
  my_shelter.Enqueue(cat_type);
  my_shelter.Enqueue(dog_type);
  my_shelter.Enqueue(cat_type);
  my_shelter.Enqueue(dog_type);
  my_shelter.DequeueCat();
  my_shelter.Print(); // ok, end --> dog cat dog dog <-- begin
  my_shelter.DequeueCat();
  my_shelter.Print(); // ok, end --> dog dog dog <-- begin
  return 0;
}