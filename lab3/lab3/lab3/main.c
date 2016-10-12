/*-------------------------------------------------*/
/* Zack Waller                                     */
/* Lab 3                                           */
/* Figure the perimeter and area of a polygon      */
/* surrounded by a circle                          */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define IN_FILE "/Users/Zack/Documents/c/lab3/lab3/lab3/lab3.dat"
#define OUT_FILE "/Users/Zack/Documents/c/lab3/lab3/lab3/lab3.txt"

//function prototypes
double calcArea(double,double);
double calcPerimeter(double,double);
void writeHeaders(FILE *writefile);
void writeLine(FILE *writefile, double, double, double, double);

int main(void)
{
    
    FILE *readfile;
    FILE *writefile;
    readfile = fopen(IN_FILE, "r");
    if (readfile == NULL)
    {
        printf("Error opening readfile.\n\n");
    }
    else
    {
        writefile = fopen(OUT_FILE, "w+");
        if (writefile == NULL)
        {
            printf("Error opening output file.\n\n");
        }
        else
        {
            writeHeaders(writefile);
            double radius, sides;
            
            while (fscanf(readfile,"%lf %lf",&radius,&sides )!= EOF)
            {
                //Do calcs then write.
                double perimeter = calcPerimeter(sides,radius);
                double area = calcArea(sides,radius);
                writeLine(writefile, radius, sides, perimeter, area);
            }
            fclose(writefile);
        }
        
        fclose(readfile);
    }
    
    return EXIT_SUCCESS;
}

double calcArea(double n_sides, double radius)
{
    return 0.5 * n_sides * pow(radius,2.0) * sin((2.0*M_PI)/n_sides);
}
double calcPerimeter(double n_sides, double radius)
{
    return 2.0*n_sides*radius*(sin(M_PI/n_sides));
}
void writeHeaders(FILE *writefile)
{
    fprintf(writefile, "\nZack Waller.  Lab 3.\n\n");
    fprintf(writefile, "            Number      Perimeter      Area Of  \n");
    fprintf(writefile, " Radius    Of Sides    Of Polygon      Polygon  \n");
    fprintf(writefile, "--------   --------   ------------   ----------- \n");
}

void writeLine(FILE *writefile, double radius, double sides, double perimeter, double area)
{
    fprintf(writefile, "%8.2f %10.2f %14.4f %13.4f\n",radius,sides,perimeter,area);
}