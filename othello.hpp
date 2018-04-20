# ifndef DSAOTHELLO_HPP
# define DSAOTHELLO_HPP

# include "OthelloAI.hpp" // provided
# include <vector>

using namespace std;

namespace anandds
{

  class DSAOthello : public OthelloAI  // OthelloAI base class provided. DSAOthello creates AI algorithm to play game. 
  {
    
  public:

    /** Default constructor for DSAOthello AI alg
     */
    DSAOthello();
    
    
    /** Returns vector of pairs holding coordinates for possible moves
     */
    vector<pair<int,int>> possible_moves(const OthelloGameState& state);


    /** Evaluates current gamestate board 
     */ 
    int evaluate(const OthelloGameState& state);
    
    
    /** Searches down tree to evaluate what the ideal move is
     */
    int recursive_search(OthelloGameState& state, int depth);


    /** Keeps track of best move as algorithm checks all valid moves
     */
    //pair<int,int> best_move(const OthelloGameState& state,
    //                        pair<int,int> current_move);
 
    
    /** Built on base class function in OthelloAI
     */
    virtual std::pair<int, int> chooseMove(const OthelloGameState& state);


  private:
    OthelloCell myturn;
    
  };
 
}

# endif // DSAOTHELLO_HPP
