#include <iostream>
#include <string>
#include <exception>
using namespace std;

class IndexOutOfBounds : public std::exception
{
public:
  const char *what() const noexcept override
  {
    return "Index out of bounds";
  }
};

class GameEntry
{
public:
  GameEntry(const string &n = "", int s = 0) : _name(n), _score(s){};
  string getName() const { return _name; }

  int getScore() const { return _score; };

private:
  string _name;
  int _score;
};

class Scores
{ // stores game high scores
public:
  Scores(int maxEnt = 10);      // constructor
  ~Scores();                    // destructor
  void add(const GameEntry &e); // add a game entry
  void remove(int i)            // remove the ith entry
      throw(IndexOutOfBounds);
  void print() const;

private:
  int _maxEntries;     // maximum number of entries
  int _numEntries;     // actual number of entries
  GameEntry *_entries; // array of game entries
};

Scores::Scores(int maxEnt) : _maxEntries(maxEnt), _numEntries(0), _entries(new GameEntry[maxEnt]) { cout << "Object score created \n"; };

Scores::~Scores() { delete[] _entries; }

void Scores::add(const GameEntry &e)
{
  int score = e.getScore();
  // Check if all the array is full
  if (_numEntries == _maxEntries)
  {
    if (score < _entries[_maxEntries - 1].getScore())
    {
      cout << "The score is too low \n";
      return; // the score of the new GameEntry is lower than the lowest score in the array
    }
  }
  else
  {
    _numEntries++;
  }
  // shift all the lower object to the right by copying the value from the right
  int lastPosition = _numEntries - 2;
  while (lastPosition >= 0 && _entries[lastPosition].getScore() < score)
  {
    _entries[lastPosition + 1] = _entries[lastPosition];
    lastPosition--;
  }

  _entries[lastPosition + 1] = e;
  cout << "Added " << e.getScore() << "\n";
}

void Scores::print() const
{
  for (int i = 0; i < _numEntries; i++)
  {
    cout << _entries[i].getScore() << "\n";
  }
};

void Scores::remove(int i) throw(IndexOutOfBounds)
{
  if (i >= _numEntries || i < 0)
    throw IndexOutOfBounds();
  for (i; i <= _numEntries - 2; i++)
  {
    _entries[i] = _entries[i + 1];
  }
  _numEntries--;
}