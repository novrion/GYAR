#include <stdio.h>
#include <cmath>


const int kNBots = 4;
const int kNBoardTypes = 3;
const int kNPositions = 20;

const char* kBotNames[2][4] = {
  { {"           [ar base]"}, {"         [ar undo move]"}, {"         [ar alpha beta]"}, {"         [ar move order]"} }, 
  { {"           [bb base]"}, {"         [bb undo move]"}, {"         [bb alpha beta]"}, {"         [bb move order]"} }
};



int main() {

  printf("[Relative Change]   [Standard Deviation]\n\n");

  for (int bot_type = 0; bot_type < 2; ++bot_type) {


    double average_changes[kNBots][kNBoardTypes] = {};
    double average_average_changes[kNBots] = {};

    double standard_deviations[kNBots][kNBoardTypes] = {};
    double average_standard_deviations[kNBots] = {};

    double average_times[kNBots][kNBoardTypes][kNPositions] = {};
    
    for (int bot = 0; bot < kNBots; ++bot) {

      // Input
      for (int board_type = 0; board_type < kNBoardTypes; ++board_type) {
        for (int position = 0; position < kNPositions; ++position) {
          scanf("%lf", &average_times[bot][board_type][position]);
        }
      }


      // Computation
      for (int board_type = 0; board_type < kNBoardTypes; ++board_type) {
        
        // Average change
        double sum_change = 0;
        for (int position = 0; position < kNPositions; ++position) { sum_change += 1 - (average_times[bot][board_type][position] / average_times[0][board_type][position]); }
        average_changes[bot][board_type] = sum_change / (double)kNPositions;

        // Standard deviation
        double deviation_sum = 0;
        for (int position = 0; position < kNPositions; ++position) { 
          double x = 1 - (average_times[bot][board_type][position] / average_times[0][board_type][position]);
          deviation_sum += (x - average_changes[bot][board_type]) * (x - average_changes[bot][board_type]);
        }
        standard_deviations[bot][board_type] = sqrt(deviation_sum / (double)kNPositions);
      }

      // Average average changes
      double sum_average_average_change = 0;
      for (int board_type = 0; board_type < kNBoardTypes; ++board_type) { sum_average_average_change += average_changes[bot][board_type]; }
      average_average_changes[bot] = sum_average_average_change / (double)kNBoardTypes;

      // Average standard deviations
      double sum_average_standard_deviation = 0;
      for (int board_type = 0; board_type < kNBoardTypes; ++board_type) { sum_average_standard_deviation += standard_deviations[bot][board_type] * standard_deviations[bot][board_type]; }
      average_standard_deviations[bot] = sqrt(sum_average_standard_deviation) / (double)kNBoardTypes;
    }


    // Output
    for (int bot = 0; bot < kNBots; ++bot) {
      printf("   %s\n", kBotNames[bot_type][bot]);
      for (int board_type = 0; board_type < kNBoardTypes; ++board_type) {
        printf("   %.9f          %.9f\n", average_changes[bot][board_type], standard_deviations[bot][board_type]);
      }
      printf("\n");
    }

    printf("   ----------- AVERAGES -----------\n");
    for (int bot = 0; bot < kNBots; ++bot) {
      printf("   %.9f          %.9f\n", average_average_changes[bot], average_standard_deviations[bot]);
    }

    printf("\n\n\n\n\n");
  }





  return 0;
}