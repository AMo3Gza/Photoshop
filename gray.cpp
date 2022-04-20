// Program: Ass3.cpp
// Purpose: Demonstrate use of bmplip for handling
//          bmp colored and grayscale images
//          Program load a gray image and store in another file
//          12 Filters
// Author1:  Ayman Ashraf , 20210079 , A
// Author2:  Malek Khaled Mohammed, 20210320 , A
// Author3:  Ammar Ayman Mustafa, 20210253 , A
// Section : S11,12
// Date:    20 April 2022
// Version: 3.0

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
}

// Invert Image - Filter
void invertImage(){
    for (int i = 0; i <= SIZE; i++){
        for (int j = 0; j < SIZE; j++){
            newImage[i][j] = 255 - image[i][j];
        }
    }
}

// Merge Images - Filter
void mergeImages(){
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
}

//Rotate Image - Filter
void rotateImage(){
    int rotate_input;

    cout << "1- Rotate By a 90\n"
            "2- Rotate By a 180\n"
            "3- Rotate By a 270\n";
    cin >> rotate_input;

    if (rotate_input == 1){
        for (int i = 0; i < SIZE; i++){

            for (int j = 255; j > 0; j--){
                newImage[i][j] = image[j][-i];
            }
        }
    }

    if (rotate_input == 2){
         int x = 255;
         for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                newImage[x][j]= image[i][-j];
            }
            x--;
        }
    }

    if (rotate_input == 3){
         for (int i = 0; i < SIZE; i++){

            for (int j = 255; j > 0; j--){
                newImage[i][j] = image[255 - j][i - 255];
            }
        }
    }

    else{
        cout << "Invalid input\n";
        rotateImage();
    }
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
}

// Detect Image Edges - Filter
void detectImageEdges(){
    blackAndWhite();
    for(int i=0 ; i<SIZE ;i++){
        for(int j=0 ;j<SIZE ;j++){
            if (image[i][j]!=image[i+1][j+1]){
                newImage[i][j]=0;
            }
            else if(image[i][j] == image[i+1][j+1]){
                newImage[i][j]=255;

            }
        }
    }
}

//Enlarge Image - Filter
void enlargeImage(){
    int enlarge_input;
    cout << "1- Enlarge 1st Quarter \n"
            "2- Enlarge 2nd Quarter \n"
            "3- Enlarge 3rd Quarter \n"
            "4- Enlarge 4th Quarter \n";
    cin >> enlarge_input;

    if (enlarge_input == 1){
         for (int i = 0; i < 127; i++){

             for (int j = 0; j < 127; j++){
                 if (i > 0){
                 newImage[2 * i][2 * j] = image[i][j];
                 newImage[2 * i][2 * j + 1] = image[i][j];
                 newImage[2 * i + 1][2 * j] = image[i][j];
                 newImage[2 * i + 1][2 * j + 1] = image[i][j];
                }
             }
         }
    }

    if (enlarge_input == 2){
        for (int i = 0; i < 127; i++){

             for (int j = 127; j < 255; j++){
                 newImage[2 * i][2 * j] = image[i][j];
                 newImage[2 * i][2 * j + 1] = image[i][j];
                 newImage[2 * i + 1][2 * j] = image[i][j];
                 newImage[2 * i + 1][2 * j + 1] = image[i][j];
             }

         }
    }

    if (enlarge_input == 3){
        for (int i = 127; i < 255; i++){

             for (int j = 0; j < 127; j++){
                 image[2 * i][2 * j] = image[i][j];
                 image[2 * i][2 * j + 1] = image[i][j];
                 image[2 * i + 1][2 * j] = image[i][j];
                 image[2 * i + 1][2 * j + 1] = image[i][j];

             }

         }
    }

    if (enlarge_input == 4){
        for (int i = 127; i < 255; i++){

             for (int j = 127; j < 255; j++){
                 image[2 * i][2 * j] = image[i][j];
                 image[2 * i][2 * j + 1] = image[i][j];
                 image[2 * i + 1][2 * j] = image[i][j];
                 image[2 * i + 1][2 * j + 1] = image[i][j];

             }

         }
    }

    else {
        cout << "Invalid Input";
        enlargeImage();
    }
}

// Shrink Image - Filter
void shrinkImage(){
    int y = 0 , x = 0, choice, result;

    cout << "1- 1/4\n"
            "2- 1/2\n"
            "3- 1/3" << endl;
    cin >> choice;

    if (choice == 1)
        choice += 3;

    result = SIZE / choice;
    for (int i = 0 ; i < result ; i++){
        for (int j = 0 ; j < result ; j++){
            newImage[i][j] = image[y][x];
            newImage[i][j] = image[y][x];
            newImage[i][j] = image[y][x];
            x += choice;
        }
        x = 1;
        y += choice;
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
}

// Shuffle Image - Filter
void shuffleImage(){
    unsigned char first_qrt[SIZE/2][SIZE/2], second_qrt[SIZE/2][SIZE/2];
    unsigned char third_qrt[SIZE/2][SIZE/2], fourth_qrt[SIZE/2][SIZE/2];

    for (int i = 0; i < SIZE/2; i++){
        for (int j = 0; j < SIZE/2; j++){
            first_qrt[i][j] = image[i][j];
        }
    }
    for (int i = 0, x = 0; i < SIZE/2; i++, x++){
        for (int j = SIZE/2, y = 0; j < SIZE; j++, y++){
            second_qrt[x][y] = image[i][j];
        }
    }
    for (int i = SIZE/2, x = 0; i < SIZE; i++, x++){
        for (int j = 0, y = 0; j < SIZE/2; j++, y++){
            third_qrt[x][y] = image[i][j];
        }
    }
    for (int i = SIZE/2, x = 0; i < SIZE; i++, x++){
        for (int j = SIZE/2, y = 0; j < SIZE; j++, y++){
            fourth_qrt[x][y] = image[i][j];
        }
    }

    int qrt1_pos, qrt2_pos, qrt3_pos, qrt4_pos;

    cout << "First Quarter Position: ";
    cin >> qrt1_pos;

    cout << "Second Quarter Position: ";
    cin >> qrt2_pos;

    cout << "Third Quarter Position: ";
    cin >> qrt3_pos;

    cout << "Fourth Quarter Position: ";
    cin >> qrt4_pos;

    if (qrt1_pos == 1){
        for (int i = 0, x = 0; i < SIZE/2; i++, x++){
            for (int j = 0, y = 0; j < SIZE/2; j++, y++){
                newImage[i][j] = first_qrt[x][y];
            }
        }
    }
    if (qrt1_pos == 2){
        for (int i = 0, x = 0; i < SIZE/2; i++, x++){
            for (int j = SIZE/2, y = 0; j < SIZE; j++, y++){
                newImage[i][j] = first_qrt[x][y];
            }
        }
    }
    if (qrt1_pos == 3){
        for (int i = SIZE/2, x = 0; i < SIZE; i++, x++){
            for (int j = 0, y = 0; j < SIZE/2; j++, y++){
                newImage[i][j] = first_qrt[x][y];
            }
        }
    }
    if (qrt1_pos == 4){
        for (int i = SIZE/2, x = 0; i < SIZE; i++, x++){
             for (int j = SIZE/2, y = 0; j < SIZE; j++, y++){
                newImage[i][j] = first_qrt[x][y];
            }
        }
    }

    if (qrt2_pos == 1){
        for (int i = 0, x = 0; i < SIZE/2; i++, x++){
            for (int j = 0, y = 0; j < SIZE/2; j++, y++){
                newImage[i][j] = second_qrt[x][y];
            }
        }
    }
    if (qrt2_pos == 2){
        for (int i = 0, x = 0; i < SIZE/2; i++, x++){
            for (int j = SIZE/2, y = 0; j < SIZE; j++, y++){
                newImage[i][j] = second_qrt[x][y];
            }
        }
    }
    if (qrt2_pos == 3){
        for (int i = SIZE/2, x = 0; i < SIZE; i++, x++){
            for (int j = 0, y = 0; j < SIZE/2; j++, y++){
                newImage[i][j] = second_qrt[x][y];
            }
        }
    }
    if (qrt2_pos == 4){
        for (int i = SIZE/2, x = 0; i < SIZE; i++, x++){
             for (int j = SIZE/2, y = 0; j < SIZE; j++, y++){
                newImage[i][j] = second_qrt[x][y];
            }
        }
    }

    if (qrt3_pos == 1){
        for (int i = 0, x = 0; i < SIZE/2; i++, x++){
            for (int j = 0, y = 0; j < SIZE/2; j++, y++){
                newImage[i][j] = third_qrt[x][y];
            }
        }
    }
    if (qrt3_pos == 2){
        for (int i = 0, x = 0; i < SIZE/2; i++, x++){
            for (int j = SIZE/2, y = 0; j < SIZE; j++, y++){
                newImage[i][j] = third_qrt[x][y];
            }
        }
    }
    if (qrt3_pos == 3){
        for (int i = SIZE/2, x = 0; i < SIZE; i++, x++){
            for (int j = 0, y = 0; j < SIZE/2; j++, y++){
                newImage[i][j] = third_qrt[x][y];
            }
        }
    }
    if (qrt3_pos == 4){
        for (int i = SIZE/2, x = 0; i < SIZE; i++, x++){
             for (int j = SIZE/2, y = 0; j < SIZE; j++, y++){
                newImage[i][j] = third_qrt[x][y];
            }
        }
    }

    if (qrt4_pos == 1){
        for (int i = 0, x = 0; i < SIZE/2; i++, x++){
            for (int j = 0, y = 0; j < SIZE/2; j++, y++){
                newImage[i][j] = fourth_qrt[x][y];
            }
        }
    }
    if (qrt4_pos == 2){
        for (int i = 0, x = 0; i < SIZE/2; i++, x++){
            for (int j = SIZE/2, y = 0; j < SIZE; j++, y++){
                newImage[i][j] = fourth_qrt[x][y];
            }
        }
    }
    if (qrt4_pos == 3){
        for (int i = SIZE/2, x = 0; i < SIZE; i++, x++){
            for (int j = 0, y = 0; j < SIZE/2; j++, y++){
                newImage[i][j] = fourth_qrt[x][y];
            }
        }
    }
    if (qrt4_pos == 4){
        for (int i = SIZE/2, x = 0; i < SIZE; i++, x++){
             for (int j = SIZE/2, y = 0; j < SIZE; j++, y++){
                newImage[i][j] = fourth_qrt[x][y];
            }
        }
    }
}

// Blur Image - Filter
void blurImage(){
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            newImage[i][j] = ((image[i][j])+(image[i-1][j-1])+(image[i-1][j])+(image[i-1][j+1])
                    +(image[i][j-1])+(image[i][j+1])+(image[i+1][j-1])+(image[i+1][j])+(image[i+1][j+1])
                    +(image[i-2][j-2])+(image[i-2][j-1])+(image[i-2+1][j])+(image[i-2][j+1])+(image[i-2][j+2])
                    +(image[i-1][j-2])+(image[i-1][j+2])+(image[i][j-2])+(image[i][j+2])+(image[i+1][j-2])
                    +(image[i+1][j+2])+(image[i+2][j-2])+(image[i+2][j-1])+(image[i+2][j])+(image[i+2][j+1])
                    +(image[i+2][j+2]))/25;
        }
    }
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
            "5- Rotate Image\n"
            "6- Darken and Lighten Image \n"
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
        cout << "Black and White Image Filter is Done"<< endl;
    }else if(choice == '2'){
        invertImage();
        multiTask();
        cout << "Invert Image Filter is Done"<< endl;
    }else if (choice == '3'){
        mergeImages();
        multiTask();
        cout << "Merge Images Filter is Done"<< endl;
    }else if (choice == '4'){
        flipImage();
        multiTask();
        cout << "Flip Image Filter is Done"<< endl;
    }else if (choice == '5'){
        rotateImage();
        multiTask();
        cout << "Rotate Image Filter is Done" << endl;
    }else if (choice == '6'){
        darkenAndLightenImage();
        multiTask();
        cout << "Darken and Lighten Image Filter is Done"<< endl;
    }else if (choice == '7'){
        detectImageEdges();
        multiTask();
        cout << "Detect Image Edges Filter is Done" << endl;
    }else if (choice == '8'){
        enlargeImage();
        multiTask();
        cout << "Enlarge Image Filter is Done" << endl;
    }else if (choice == '9'){
        shrinkImage();
        multiTask();
        cout << "Shrink Image Filter is Done" << endl;
    }else if (choice == 'a'){
        mirrorImage();
        multiTask();
        cout << "Mirror 1/2 Image Filter is Done"<< endl;
    }else if (choice == 'b'){
        shuffleImage();
        multiTask();
        cout << "Shuffle Image Filter is Done" << endl;
    }else if (choice == 'c'){
        blurImage();
        multiTask();
        cout << "Blur Image Filter is Done" << endl;
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

