//
//  AlphaBeta.cpp
//  ConnectGame
//
//  Created by Erik Buck on 6/5/13.
//  Updated assignment: Kevin Porter
//

#include "AlphaBeta.h"
#include "ConnectBoard.h"
#include <cassert>


/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
/// See comments in header.
int AbstractBoard::makeAutomaticPlayerMove(
   AbstractBoard::player player,
   AbstractBoard *&resultingBoard)
{
   return this->alphaBeta(player, resultingBoard);
}


/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
/// See comments in header.
int AbstractBoard::alphaBeta(
   AbstractBoard::player player,
   AbstractBoard *&nextBoardPtr,
   int depth,
   int alpha,
   int beta)
{
   int score = this->score();
   nextBoardPtr = NULL;

   AbstractBoard::boards availableMoves =
      allLegalMovesForPlayer(player);

   if(AbstractBoard::None != winner())
   {  // winner found
      return score;
   }
   /*
   * WARNING: An evaluation depth of 9 or more starts to use a tremendous
   * amount of memory (4GB+). If memory constrained, adjust the depth to
   * 8 or less.
   */
   else if(evaluationDepth() <= depth ||
      0 == availableMoves.size())
   {  // search limit reached or no legal moves
      return score;
   }
   else
   {

      // This default implementation makes no attempt to find
      // a winning play. You must implement a better algorithm
	  // enabling the computer to pick the best available play
	  // each turn.
      AbstractBoard::boards::iterator it(
         availableMoves.begin());
      /* Just a pointer to our board that we will assign to nextBoardPtr.
      *  Using this variable prevents nextBoardPtr from being constantly
      *  overwritten.
      */
      AbstractBoard *return_board = NULL;

      /*
      * This conditional breaks out into two nearly identical algorithms.
      * Each player is either a minimizer or a maximizer. It will recursively
      * call alphabeta(), looking for the next likely move, until either there
      * are no moves left (board filled or winner declared) or until the max
      * depth search (default 9, in AlphaBeta.h) is reached.
      */

      if (player == AbstractBoard::Maximizer) {
         int max_value = INT_MIN;
         int check_value = 0;
         while (it != availableMoves.end()) {
            // These first checks are not necessary, however, they help significantly with memory usage.
            if ((*it)->scoreForMaximizerWin() == (*it)->score()) {
               max_value = (*it)->scoreForMaximizerWin();
               return_board = (*it);
               break;
            } else if ((*it)->scoreForMinimizerWin() != (*it)->score()) {
               check_value = (*it)->alphaBeta(AbstractBoard::Minimizer, nextBoardPtr, depth + 1, alpha, beta);
               if (check_value > max_value) {
                  max_value = check_value;
                  if (max_value > alpha) {
                     alpha = max_value;
                  }
                  if (depth == 0) {
                     return_board = (*it);
                  }
                  if (beta <= alpha) {
                     break;
                  }
               }
            }
            ++it;
         }
         score = max_value;
      } else {
         int min_value = INT_MAX;
         int check_value = 0;
         while (it != availableMoves.end()) {
            // These first checks are not necessary, however, they help significantly with memory usage.
            if ((*it)->scoreForMinimizerWin() == (*it)->score()) {
               min_value = (*it)->scoreForMinimizerWin();
               return_board = (*it);
               break;
            } else if ((*it)->scoreForMaximizerWin() != (*it)->score()) {
               check_value = (*it)->alphaBeta(AbstractBoard::Maximizer, nextBoardPtr, depth + 1, alpha, beta);
               if (check_value < min_value) {
                  min_value = check_value;
                  if (min_value < beta) {
                     beta = min_value;
                  }
                  if (depth == 0) {
                     return_board = (*it);
                  }
                  if (beta <= alpha) {
                     break;
                  }
               }
            }
            ++it;
         }
         score = min_value;
      }

      if (depth == 0 && return_board != NULL) {
         nextBoardPtr = return_board;
         return_board = NULL;
         return nextBoardPtr->score();
      } else if (depth == 0) {
         //assert(return_board != NULL);
         // I have not encountered this happening, but just in case the
         // algorithm fails, pick a random(ish) move.
         --it;
         nextBoardPtr = (*it);
      } else {
         return score;
      }
   }
   /*
   * This should never happen, but I was getting compiler warnings. The game should break if it reaches
   * this point.
   */
   assert(false);
   return 0;
}
