// Program: demo2.cpp
// Purpose: Demonstrate use of bmplip for handling
//          bmp colored and grayscale images
//          Program load a gray image and store in another file
//          6 Filters
// Author1:  Ayman Ashraf , 20210079 , A
// Author2:  Malek Khaled mohammed, 20210320 , A
// Author3:  Ammar Ayman mustafa, 20210253 , A
// Section : S11,12
// Date:    7 April 2022
// Version: 1.0

#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include "bmplib.cpp"

using namespace std;

unsigned char image[SIZE][SIZE][RGB],newImage[SIZE][SIZE][RGB];
int loaded=0;

// This saves the result values in the main image to continue
void multiTask(){
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            for (int k=0; k<RGB;k++){
                image[i][j][k]= newImage[i][j][k];
            }
        }
    }
}

//Image Loader - Filter
void loadImage() {
   char imageFileName[100];

   // Get gray scale image file name
   cout << "Enter the source image file name: ";
   cin >> imageFileName;

   // Add to it .bmp extension and load image
   strcat (imageFileName, ".bmp");
   readRGBBMP(imageFileName, image);
   loaded = 1;
}

// Image Saver - Filter
void saveImage() {
   char imageFileName[100];

   // Get gray scale image target file name
   cout << "Enter the target image file name: ";
   cin >> imageFileName;

   // Add to it .bmp extension and load image
   strcat (imageFileName, ".bmp");
   writeRGBBMP(imageFileName, newImage);
}

// Black and White Image - Filter
void blackAndWhite(){
    int avg;
     for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            avg = (image[i][j][0] + image[i][j][1] +image[i][j][2])/3;
            for (int k =0; k< RGB; k++){
                newImage[i][j][k] =avg;
            }
        }
     }
    cout << "Done"<< endl;
}

// Flip Image - Filter
void flipImage(){
    int choice, x=255, y=255;
    cout << "1- Vertical\n"
            "2- Horizontal\n";
    cin >> choice;
    // Vertical
    if (choice == 1){
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                for(int k=0; k<RGB;k++){
                    newImage[x][j][k]= image[i][j][k];
                }
            }
            x--;
        }
    }
    // Horizontal
    else if (choice == 2){
         for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                for(int k = 0; k < RGB; k++){
                    newImage[i][y][k]= image[i][j][k];
                }
                y--;
                if (y == 0)
                    y+= SIZE;
            }
        }
    }
    cout << "Done "<< endl;
}



// Mirror 1/2 Image - Filter
void mirrorImage(){
    int choice,x=255;
    cout << "1- Left \n"
            "2- Right \n"
            "3- Upper \n"
            "4- Lower \n";
    cin >> choice;
    if (choice == 1){
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < (SIZE/2); j++) {
                for (int k =0; k< RGB; k++){
                    newImage[i][j][k]= image[i][j][k];
                    newImage[i][x][k]= image[i][j][k];
                }
                x--;
                if (x==127)
                    x+=(SIZE/2);
            }
        }
    }
    else if (choice == 2){
        int y = (SIZE/2);
        for (int i = 0; i < SIZE; i++) {
            for (int j = (SIZE/2); j <SIZE; j++) {
                for (int k =0; k< RGB; k++){
                    newImage[i][j][k]= image[i][j][k];
                    newImage[i][y][k]= image[i][j][k];
                }
                y--;
                if (y==0)
                    y+=(SIZE/2);
            }
        }
    }
    else if (choice == 3){
        for (int i = 0; i < (SIZE/2); i++){
            for (int j = 0; j < SIZE; j++){
                for (int k =0; k< RGB; k++){
                    newImage[i][j][k]= image[i][j][k];
                    newImage[x][j][k]= image[i][j][k];
                }
            }
            x--;
        }
    }
    else if (choice == 4){
        int z =127;
        for (int i = (SIZE/2); i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                for (int k =0; k< RGB; k++){
                    newImage[i][j][k]= image[i][j][k];
                    newImage[z][j][k]= image[i][j][k];
                }
            }
            z--;
        }
    }
    cout << "Done"<< endl;
}

// Main Menu
int main(){
    char choice;

    if (loaded == 0)
        loadImage();

    cout << "1- Black and White Image\n"
            "2- Invert Image\n"
            "3- Merge Images\n"
            "4- Flip Image\n"
            "5- Darken and Lighten Image \n"
            "6- Rotate Image\n"
            "7- Detect Image Edges\n"
            "8- Enlarge Image\n"
            "9- Shrink Image\n"
            "a- Mirror 1/2 Image\n"
            "b- Shuffle Image\n"
            "c- Blur Image\n"
            "0- Save The image to a file\n";
    cin >> choice;

    if (choice == '1'){
        blackAndWhite();
        multiTask();
    }else if(choice == '2'){

        multiTask();
    }else if (choice == '3'){

        multiTask();
    }else if (choice == '4'){
        flipImage();
        multiTask();
    }else if (choice == '5'){

        multiTask();
    }else if (choice == '6'){

        multiTask();
    }else if (choice == '7'){

        multiTask();
    }else if (choice == '8'){

        multiTask();
    }else if (choice == '9'){

        multiTask();
    }else if (choice == 'a'){
        mirrorImage();
        multiTask();
    }else if (choice == '0'){
        saveImage();
        multiTask();
        cout << "Goodbye";
        return 1;
    }else{
        cout << "\nInvalid input" << endl;
    }
    main();
    return 0;
}

