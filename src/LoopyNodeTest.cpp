#include "LoopyNode.h"
#include "LoopyInputNode.h"
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <vector>

#include "BasicLoopyNodes.h"
#include "LinearTransformations.h"
#include "MathNodes.h"
#include "LoopyGraphState.h"

int main()
{
    cv::namedWindow( "Display window", cv::WINDOW_AUTOSIZE );// Create a window for display.

    std::cout << "F: enter new file path to read\n" <<
                 "R: Refresh the graph using the current file\n";
    std::cout << "To start, type in a path to a graph file: ";
    std::string file;
    cin >> file;

    LoopyGraphState lgs;
    lgs.readGraphFromFile(file);

    while (true) {
        lgs.setAllInputsReady();

        cv::imshow( "Display window", lgs.output->getOutput() );
        int key = cv::waitKey(0);
        // 114 = r
        if (key == 114) {
            lgs.destroyAll();
            lgs.readGraphFromFile(file);
        }

        if (key == 102) {
            cout << "Type in a path to a graph file: ";
            cin >> file;
            lgs.destroyAll();
            lgs.readGraphFromFile(file);
        }
    }
}
