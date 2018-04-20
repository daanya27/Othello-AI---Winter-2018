# include "DSAOthello.hpp"
# include <iostream>
# include <fstream>
# include <string>


anandds::DSAOthello::DSAOthello()
{
} 


vector<pair<int,int>> anandds::DSAOthello::possible_moves
  (const OthelloGameState& state)
{
  vector<pair<int,int>> possible;
  
  const OthelloBoard& board = state.board();
  for (int x = 0; x < board.width(); x++) {
    for (int y = 0; y < board.height(); y++) {
      if (state.isValidMove(x,y)) {
        possible.push_back(make_pair(x,y));
      }
    }
  }

  return possible;
}


int anandds::DSAOthello::evaluate(const OthelloGameState& state)
{
  int score = 0;
  const OthelloBoard& board = state.board();
  if (board.cellAt(0,0) == myturn) {
    score += 5;
  }
  if (board.cellAt(0,board.height()-1) == myturn) {
    score += 5;
  }
  if (board.cellAt(board.width()-1,0) == myturn) {
    score += 5;
  }
  if (board.cellAt(board.width()-1,board.height()-1) == myturn) {
    score += 5;
  } 
  if (myturn == OthelloCell::black) {
    score += state.blackScore() - state.whiteScore();
  } else {
    score +=  state.whiteScore() - state.blackScore();
  }
  return score;
}


int anandds::DSAOthello::recursive_search(OthelloGameState& state, int depth)
{
  if (depth == 0) {
    return evaluate(state); 
  }

  if ((myturn == OthelloCell::black && state.isBlackTurn()) ||
      (myturn == OthelloCell::white && state.isWhiteTurn())) {

    int max_score = -1000;
    
    vector<pair<int,int>> possible = possible_moves(state);
    
    pair<int,int> current_move;   // declaring vars for for loop 4 lines down
    unique_ptr<OthelloGameState> cloned_state;
  
    for (int i = 0; i < possible.size(); i++) {
      current_move = possible[i];
      cloned_state = state.clone();
      cloned_state->makeMove(current_move.first, current_move.second);
      max_score = max(max_score,
                       recursive_search(*cloned_state, depth-1));
    }
    return max_score; 

  } else if ((myturn == OthelloCell::black && state.isWhiteTurn()) ||
             (myturn == OthelloCell::white && state.isBlackTurn())) {


    int min_score = 1000;
    
    vector<pair<int,int>> possible = possible_moves(state);
    
    pair<int,int> current_move;   // declaring vars for for loop 4 lines down
    unique_ptr<OthelloGameState> cloned_state;
  
    for (int i = 0; i < possible.size(); i++) {
      current_move = possible[i];
      cloned_state = state.clone();
      cloned_state->makeMove(current_move.first, current_move.second);
      min_score = min(min_score, recursive_search(*cloned_state, depth-1));
    }
    return min_score; 
  }
  
  return 0;
}


std::pair<int, int> anandds::DSAOthello::chooseMove(const OthelloGameState&
                                                    state)
{
  pair<int,int> best_move = make_pair(0,0);
  int highest_score = -100000;
  int recursion_depth = 2;

  vector<pair<int,int>> possible = possible_moves(state);
  if (possible.size() < 10) {
    recursion_depth = 3;
  }

  pair<int,int> current_move;   // declaring vars for for loop 4 lines down
  unique_ptr<OthelloGameState> cloned_state;
  int current_score;

  if (state.isBlackTurn()) {      // setting turn value
    myturn = OthelloCell::black;
  } else if (state.isWhiteTurn()) {
    myturn = OthelloCell::white;
  }
  
  for (int i = 0; i < possible.size(); i++) {
    current_move = possible[i];
    cloned_state = state.clone();
    cloned_state->makeMove(current_move.first, current_move.second);
    current_score = recursive_search(*cloned_state, recursion_depth);

    if (current_score > highest_score) {
      highest_score = current_score;
      best_move = current_move;
    }
  }

  //best_move = possible[0];
  return best_move;
}
