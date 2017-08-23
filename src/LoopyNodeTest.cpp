#include "LoopyNode.h"
#include "LoopyInputNode.h"
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <vector>

#include "BasicLoopyNodes.h"
#include "LinearTransformations.h"
#include "LoopyGraphState.h"
#include <fstream>

using namespace std;

ifstream readFileName()
{
    string file;
    cin >> file;
    ifstream ifs(file);
    while (ifs.fail()) {
        cout << "File does not exist. Enter new file: ";
        cin >> file;
        ifs.open(file);
    }

    return ifs;
}

int main()
{
    cv::namedWindow( "Display window", cv::WINDOW_AUTOSIZE );// Create a window for display.

    cout << "F: enter new file path to read\n" <<
                 "R: Refresh the graph using the current file\n";
    cout << "To start, type in a path to a graph file: ";

    LoopyGraphState lgs;
    ifstream ifs = readFileName();
    lgs.readGraphFromFile(ifs);

    while (true) {
        lgs.setAllInputsReady();

        cv::imshow( "Display window", lgs.output->getOutput() );
        int key = cv::waitKey(0);
        // 114 = r
        if (key == 114) {
            lgs.readGraphFromFile(ifs);
        }

        if (key == 102) {
            ifs.close();
            cout << "Type in a path to a new graph file: ";
            ifs = readFileName();
            lgs.readGraphFromFile(ifs);
        }

        if (key == 113) {
            lgs.destroyAll();
            lgs.readGraphFromFile(ifs);
        }
    }
}
