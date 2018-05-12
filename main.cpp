#include "GameManager.h"
using namespace std;

int main() {

    GameManager gameManager(FILE_PLAYER, FILE_PLAYER);

    gameManager.initGame();
    gameManager.positioningStage();
    if(!gameManager.getGameStatus().isGameOn()){
        gameManager.endGame();
        return 0;
    }
    gameManager.moveStage();
    gameManager.endGame();
    return 0;
}