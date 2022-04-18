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

unsigned char image[SIZE][SIZE],newImage[SIZE][SIZE];
int loaded=0;

// This saves the result values in the main image to continue
void multiTask(){
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            image[i][j]= newImage[i][j];
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
   readGSBMP(imageFileName, image);
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
   writeGSBMP(imageFileName, newImage);
}

// Black and White Image - Filter
void blackAndWhite(){
     for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (image[i][j] > 127){
                image[i][j] = 255;
                newImage[i][j] = image[i][j];
            }else{
                image[i][j] = 0;
                newImage[i][j] = image[i][j];
            }
        }
     }
    cout << "Done  "<< endl;
}

// Invert Image - Filter
void invertImage(){
    for (int i = 0; i <= SIZE; i++){
        for (int j = 0; j < SIZE; j++){
            newImage[i][j] = 255 - image[i][j];
        }
    }
    cout << "Done"<< endl;
}

// Merge Images - Filter
void mergeFilter(){
    unsigned char imageTwo[SIZE][SIZE];
    char image2_file_name[100];
    cout << "Enter the other Image File Name to merge : ";
    cin >> image2_file_name;
    strcat(image2_file_name, ".bmp");
    readGSBMP(image2_file_name, imageTwo);
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            newImage[i][j] = (image[i][j] + imageTwo[i][j])/2;


        }
    }
    cout << "Done"<< endl;
}

// Flip Image - Filter
void flipImage(){
    int choice, x=255, y=255;;
    cout << "1- Vertical\n"
            "2- Horizontal\n";
    cin >> choice;
    // Vertical
    if (choice == 1){
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                newImage[x][j]= image[i][j];
            }
            x--;
        }
    }
    // Horizontal
    else if (choice == 2){
         for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                newImage[i][y--]= image[i][j];
                if (y == 0)
                    y+= SIZE;
            }
        }
    }
    cout << "Done"<< endl;
}

// Darken and Lighten Image - Filter
void darkenAndLightenImage(){
    int choice;
    cout << "1- Darken \n"
            "2- Lighten" << endl;
    cin >> choice;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {

            if(choice == 1)
                newImage[i][j] = (image[i][j])/2;
            else if (choice == 2)
                newImage[i][j] = ((image[i][j])/2)+ 127;
        }
    }
    cout << "Done"<< endl;
}

// Detect Image Edges - Filter
void detectImageEdges(){
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (image[i][j] > 127){
                image[i][j] = 255;
                newImage[i][j] = image[i][j];
            }else{
                image[i][j] = 0;
                newImage[i][j] = image[i][j];
            }
        }
     }
    for( int x = 0 ; x < SIZE ; x++ ){
        for( int y = 0 ; y < SIZE ; y++ ){
            if( newImage[x][y] == newImage[x+1][y+1] )
                newImage[x][y] = 255 ;
            else
                newImage[x][y] = 0;
        }
    }
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
                newImage[i][j]= image[i][j];
                newImage[i][x--]= image[i][j];
                if (x==127)
                    x+=(SIZE/2);
            }
        }
    }
    else if (choice == 2){
        int y = (SIZE/2);
        for (int i = 0; i < SIZE; i++) {
            for (int j = (SIZE/2); j <SIZE; j++) {
                newImage[i][j]= image[i][j];
                newImage[i][y--]= image[i][j];
                if (y==0)
                    y+=(SIZE/2);
            }
        }
    }
    else if (choice == 3){
        for (int i = 0; i < (SIZE/2); i++) {
            for (int j = 0; j < SIZE; j++) {
                newImage[i][j]= image[i][j];
                newImage[x][j]= image[i][j];
            }
            x--;
        }
    }
    else if (choice == 4){
        int z =127;
        for (int i = (SIZE/2); i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                newImage[i][j]= image[i][j];
                newImage[z][j]= image[i][j];
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
        invertImage();
        multiTask();
    }else if (choice == '3'){
        mergeFilter();
        multiTask();
    }else if (choice == '4'){
        flipImage();
        multiTask();
    }else if (choice == '5'){
        darkenAndLightenImage();
        multiTask();
    }else if (choice == '7'){
        detectImageEdges();
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

