#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
#include <set>
#include <cmath>
#include <algorithm>

#include <chrono>
#include <thread>

using namespace std;

vector<vector<int>> proccessInputFile(string filename) {
    string line;
    ifstream file(filename);
    getline(file, line);

    stringstream test(line);
    string segment;

    vector<vector<int>> matrix;

    getline(test, segment, ' ');
    int h = stoi(segment);

    getline(test, segment, ' ');
    int w = stoi(segment);

    vector<int> row;

    for (int i = 0; i < h; ++i) {
        getline(file, line);
        for (int j = 0; j < w; ++j) {
            int value = (int) line[j] - '0';
            row.push_back(value);
        }
        matrix.push_back(row);
        row.clear();
    }

    file.close();
    return matrix;
}

void dfs(int row, int col, vector<vector<int >> &visited, vector<vector<int >> &matrix, vector<pair<int, int >> &vec, int rowBase,
         int columnBase) {
    // mark the cell as visited
    visited[row][col] = 1;

    // coordinates - base coordinates
    vec.push_back({row - rowBase, col - columnBase});

    int n = matrix.size();
    int m = matrix[0].size();

    // delta row and delta column
    int delrow[] = {-1, 0, +1, 0};
    int delcol[] = {0, -1, 0, +1};

    // traverse all 4 neighbours
    for (int i = 0; i < 4; i++) {
        int nrow = row + delrow[i];
        int ncol = col + delcol[i];
        // check for valid unvisited land neighbour coordinates
        if (nrow >= 0 && nrow < n && ncol >= 0 && ncol < m &&
            !visited[nrow][ncol] && matrix[nrow][ncol] == 1) {
            dfs(nrow, ncol, visited, matrix, vec, rowBase, columnBase);
        }
    }
}

vector<vector<pair<int, int >>> setToOriginOfCoordinateSystem(vector<vector<pair<int, int >>> microorganisms, int start) {
    //organizme poravnamo tako, da bo najbolj levo polje na x-koordinati 0, najbolj spodnje pa na y-koordinati 0.
    for (int i = start; i < microorganisms.size(); ++i) {
        int biggestFirst = std::min_element(microorganisms[i].cbegin(), microorganisms[i].cend(), [](const auto &lhs, const auto &rhs) {
            return lhs.first > rhs.first;
        })->first;

        int smallestFirst = std::min_element(microorganisms[i].cbegin(), microorganisms[i].cend(), [](const auto &lhs, const auto &rhs) {
            return lhs.first < rhs.first;
        })->first;

        int smallestSecond = std::min_element(microorganisms[i].cbegin(), microorganisms[i].cend(), [](const auto &lhs, const auto &rhs) {
            return lhs.second < rhs.second;
        })->second;

        int biggestSecond = std::min_element(microorganisms[i].cbegin(), microorganisms[i].cend(), [](const auto &lhs, const auto &rhs) {
            return lhs.second > rhs.second;
        })->second;

        for (int j = 0; j < microorganisms[i].size(); ++j) {
            microorganisms[i][j].first = biggestFirst - microorganisms[i][j].first;
            microorganisms[i][j].second = microorganisms[i][j].second - smallestSecond;
        }
        sort(microorganisms[i].begin(), microorganisms[i].end());
    }

    return microorganisms;
}

vector<pair<int, int >> setToOriginOfCoordinateSystem(vector<pair<int, int >> microorganism) {
    //organizme poravnamo tako, da bo najbolj levo polje na x-koordinati 0, najbolj spodnje pa na y-koordinati 0.
    int biggestFirst = std::min_element(microorganism.cbegin(), microorganism.cend(), [](const auto &lhs, const auto &rhs) {
        return lhs.first > rhs.first;
    })->first;

    int smallestFirst = std::min_element(microorganism.cbegin(), microorganism.cend(), [](const auto &lhs, const auto &rhs) {
        return lhs.first < rhs.first;
    })->first;

    int smallestSecond = std::min_element(microorganism.cbegin(), microorganism.cend(), [](const auto &lhs, const auto &rhs) {
        return lhs.second < rhs.second;
    })->second;

    for (int i = 0; i < microorganism.size(); ++i) {
        microorganism[i].first = microorganism[i].first - smallestFirst;
        microorganism[i].second = microorganism[i].second - smallestSecond;
    }
    sort(microorganism.begin(), microorganism.end());

    return microorganism;
}

size_t hashOfVector(vector<pair<int, int>> &vec) {
    size_t seed = vec.size();
    for (int i = 0; i < vec.size(); ++i) {
        seed ^= vec[i].first + vec[i].second + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    }
    return seed;
}

vector<pair<int, int>> rotateMicroorganism(vector<pair<int, int>> vec, double theta) {

    //If you rotate point (px, py) around point (ox, oy) by angle theta you'll get:
    for (int i = 0; i < vec.size(); ++i) {
        int x = vec[i].first;
        int y = vec[i].second;

        double cosTheta = cos(theta);
        float sinTheta = sin(theta);

        //90 deg
        if (theta == 90 * (3.1415 / 180) || theta == -90 * (3.1415 / 180)) {
            cosTheta = 0;
            sinTheta = 1;
        }
            //180 deg
        else if (theta == 180 * (3.1415 / 180) || theta == -180 * (3.1415 / 180)) {
            cosTheta = -1;
            sinTheta = 0;
        }
            //270 deg
        else if (theta == 270 * (3.1415 / 180) || theta == -270 * (3.1415 / 180)) {
            cosTheta = 0;
            sinTheta = -1;
        }

        //X=xcos(θ)+ysin(θ)
        int newX = x * cosTheta + y * sinTheta;
        vec[i].first = newX;

        //Y=−xsin(θ)+ycos(θ)
        int newY = -x * sinTheta + y * cosTheta;
        vec[i].second = newY;
    }

    return vec;
}

int countMicroorganisms(vector<vector<int >> &matrix) {
    int n = matrix.size();
    int m = matrix[0].size();
    vector<vector<int >> vis(n, vector<int>(m, 0));
    vector<vector<pair<int, int >>> microorganisms;

    //every element in matrix is the same
    if (std::adjacent_find(matrix.begin(), matrix.end(), std::not_equal_to<>()) == matrix.end()) {
        return matrix[0][0];
    }

    // traverse the matrix
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            // if not visited and is a land cell
            if (!vis[i][j] && matrix[i][j] == 1) {
                vector<pair<int, int >> vec;
                dfs(i, j, vis, matrix, vec, i, j);
                // store in set
                microorganisms.push_back(vec);
            }
        }
    }


    //organizme poravnamo tako, da bo najbolj levo polje na x-koordinati 0, najbolj spodnje pa na y-koordinati 0.
    microorganisms = setToOriginOfCoordinateSystem(microorganisms, 0);
    int nextStart = microorganisms.size();

    vector<size_t> hashValues;

    for (int i = 0; i < microorganisms.size(); ++i) {
        size_t hash = hashOfVector(microorganisms[i]);
        hashValues.push_back(hash);
    }

    for (int i = 0; i < microorganisms.size(); ++i) {
        if (microorganisms[i].size() > 1) {
            for (int j = 0; j < 3; ++j) {
                double theta = (-90 * (j + 1)) * (3.1415 / 180);
                vector<pair<int, int>> rotatedMicroorganism = rotateMicroorganism(microorganisms[i], theta);
                rotatedMicroorganism = setToOriginOfCoordinateSystem(rotatedMicroorganism);
                size_t hash = hashOfVector(rotatedMicroorganism);
                if (hash < hashValues[i]) {
                    hashValues[i] = hash;
                }
            }
        }
    }

    sort(hashValues.begin(), hashValues.end());
    hashValues.erase(unique(hashValues.begin(), hashValues.end()), hashValues.end());

    return hashValues.size();
}


int main(int argc, char** argv) {

    if (argc != 2) {
        cout << "Napacno stevilo argumentov" << endl;
        cout << "zazeni kot: ./a.exe {.txt datoteka}" << endl;
        return -1;
    }

    string filename = argv[1];

//    string filename = R"(C:\Users\janpu\Downloads\mikroorganizmi\test09.in)";
    std::cout << "Sleep 1" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    vector<vector<int>> matrix = proccessInputFile(filename);

    vector<vector<int>> visited(matrix.size(), vector<int>(matrix[0].size(), 0));

    std::cout << "Sleep 2" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    cout << countMicroorganisms(matrix) << endl;

    std::cout << "Sleep 3" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));

    return 0;
}