#include <stdio.h>


const int kNBots = 4;
const int kNBoardTypes = 3;
const int kNPositions = 20;

const char* kBotNames[2][4] = {
  { {"ar base"}, {"ar undo move"}, {"ar alpha beta"}, {"ar move order"} }, 
  { {"bb base"}, {"bb undo move"}, {"bb alpha beta"}, {"bb move order"} }
};



int main() {

  for (int bot_type = 0; bot_type < 2; ++bot_type) {

    double average_standard_deviations[kNBots][kNBoardTypes];
    double average_changes[kNBots][kNBoardTypes];
    double average_times[kNBots][kNBoardTypes][kNPositions];
    
    for (int bot = 0; bot < kNBots; ++bot) {

      // Input
      for (int board_type = 0; board_type < kNBoardTypes; ++board_type) {
        for (int position = 0; position < kNPositions; ++position) {
          scanf(" %lf", &average_times[bot][board_type][position]);
        }
      }

      for (int board_type = 0; board_type < kNBoardTypes; ++board_type) {
        scanf(" %lf", &average_standard_deviations[bot][board_type]);
      }


      // Computation
      for (int board_type = 0; board_type < kNBoardTypes; ++board_type) {
        double sum_change = 0;
        for (int position = 0; position < kNPositions; ++position) { sum_change += (average_times[bot][board_type][position] / average_times[0][board_type][position]); 
        printf("1: %lf         2:  %lf     ans: %lf\n", average_times[bot][board_type][position], average_times[0][board_type][position], average_times[bot][board_type][position] / average_times[0][board_type][position]); }
        average_changes[bot][board_type] = sum_change / (double)kNPositions;
      }
    }


    // Output
    for (int bot = 0; bot < kNBots; ++bot) {
      printf("[%s]\n", kBotNames[bot_type][bot]);
      for (int board_type = 0; board_type < kNBoardTypes; ++board_type) {
        printf("%lf     %lf\n", average_changes[bot][board_type], average_standard_deviations[bot][board_type]);
      }
      printf("\n");
    }
    printf("\n\n");
  }





  return 0;
}