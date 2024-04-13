#include <iostream>
#include <vector>
#include <fstream>
#include <string>
using namespace std;

class Human {
private:
    string name;
    string gender;
    int height;
public:
    Human(string name, string gender, int height) {
        this->name = name;
        this->gender = gender;
        this->height = height;
    }

    string getName() {
        return name;
    }

    string getGender() {
        return gender;
    }

    int getHeight() {
        return height;
    }
};

class Cloth {
private:
    string clothName;
    string color;
    string size;
public:
    Cloth(string clothName, string color, string size) {
        this->clothName = clothName;
        this->color = color;
        this->size = size;
    }

    string getClothName() {
        return clothName;
    }

    string getColor() {
        return color;
    }

    string getSize() {
        return size;
    }
};

class Size {
private:
    string size;
    int mHeight;
    int fHeight;
public:
    Size(string size, int mHeight, int fHeight) {
        this->size = size;
        this->mHeight = mHeight;
        this->fHeight = fHeight;
    }

    string getSize() {
        return size;
    }

    int getMHeight() {
        return mHeight;
    }

    int getFHeight() {
        return fHeight;
    }
};

class FileReader {
public:
    void readFile(vector<Human>& humans) {
        ifstream file("Humans.csv");
        string line;
        while (getline(file, line)) {
            string name;
            string gender;
            int height;

            int startPos = 0;
            for (int i = 0; i < 3; i++) {
                int endPos = line.find(';', startPos);
                string token = line.substr(startPos, endPos - startPos);
                switch (i) {
                case 0:
                    name = token;
                    break;
                case 1:
                    gender = token;
                    break;
                case 2:
                    height = stoi(token);
                    break;
                }
                startPos = endPos + 1;
            }
            humans.push_back(Human(name, gender, height));
        }
        file.close();
    }

    void readFile(vector<Cloth>& clothes) {
        ifstream file("Clothes.csv");
        string line;
        while (getline(file, line)) {
            string clothName;
            string color;
            string size;

            int startPos = 0;
            for (int i = 0; i < 3; i++) {
                int endPos = line.find(';', startPos);
                string token = line.substr(startPos, endPos - startPos);
                switch (i) {
                case 0:
                    clothName = token;
                    break;
                case 1:
                    color = token;
                    break;
                case 2:
                    size = token;
                    break;
                }
                startPos = endPos + 1;
            }
            clothes.push_back(Cloth(clothName, color, size));
        }
        file.close();
    }

    void readFile(vector<Size>& sizes) {
        ifstream file("Sizes.csv");
        string line;
        while (getline(file, line)) {
            string size;
            int mHeight;
            int fHeight;

            int startPos = 0;
            for (int i = 0; i < 3; i++) {
                int endPos = line.find(';', startPos);
                string token = line.substr(startPos, endPos - startPos);
                switch (i) {
                case 0:
                    size = token;
                    break;
                case 1:
                    mHeight = stoi(token);
                    break;
                case 2:
                    fHeight = stoi(token);
                    break;
                }
                startPos = endPos + 1;
            }
            sizes.push_back(Size(size, mHeight, fHeight));
        }
        file.close();
    }

    void associateClothes(vector<Human>& humans, vector<Size>& sizes, vector<Cloth>& clothes) {
        ofstream outputFile("People.csv");
        for (Human& human : humans) {
            bool clothFound = false;
            string clothName;
            string color;
            string size;
            for (Size& s : sizes) {
                int height;
                if (human.getGender() == "Male")
                    height = s.getMHeight();
                else
                    height = s.getFHeight();

                if (height == human.getHeight()) {
                    for (Cloth& cloth : clothes) {
                        if (cloth.getSize() == s.getSize()) {
                            clothName = cloth.getClothName();
                            color = cloth.getColor();
                            size = cloth.getSize();
                            clothFound = true;
                            break;
                        }
                    }
                    break;
                }
            }

            outputFile << human.getName() << ";" << human.getGender() << ";" << human.getHeight() << ";";
            if (clothFound)
                outputFile << clothName << ";" << color << ";" << size << endl;
            else
                outputFile << "-;-;-" << endl;
        }
        outputFile.close();

        ifstream pplfile("People.csv");
        string fline;
        if (pplfile.is_open()) {
            while (getline(pplfile, fline)) {
                cout << fline << endl;
            }
        }
        pplfile.close();
    }
};

int main()
{
    FileReader reader;

    vector<Size> sizes;
    vector<Cloth> clothes;
    vector<Human> humans;

    reader.readFile(sizes);
    reader.readFile(clothes);
    reader.readFile(humans);

    reader.associateClothes(humans, sizes, clothes);
}