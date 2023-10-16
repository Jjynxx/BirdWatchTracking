#include<iostream>
#include<string>
#include<fstream>
#include<iomanip>

// Sara McHattie
// 

using namespace std;


// Global variable
const int SIZE = 25;
const int LOCATION = 3;

// function prototypes
int loadArrays(ifstream&, string[], int[][LOCATION], int);
void computeSum(int[][LOCATION], int[], int&);
void findBird(int[][LOCATION], int&, int&, int);
void mostBirdsSeen(int[], int&, int);
void printReport(ofstream&, const string[], const int[][LOCATION], int[], int, int);



int main()
{

	int sightings[SIZE][LOCATION];  //no need to change your variable names to match mine!
	string birds[SIZE];
	int totalSightings[SIZE] = { 0 };
	int noBirds = 0;
	int highestRow, highestCol, highestSighting, mostViewed;
	cout << fixed << setprecision(2);
	ifstream fin("birds.dat");
	if (!fin.is_open())
	{
		cout << "error opening birds.dat file - contact systems";
		system("pause");
		exit(-1);
	}

	ofstream fout("birds.rpt");
	if (!fout.is_open())
	{
		cout << "error opening birds.rpt file - contact systems";
		system("pause");
		exit(-2);
	}
	fout << fixed << setprecision(2);

	cout << "\n\nLoad arrays\n";
	noBirds = loadArrays(fin, birds, sightings, noBirds);
	cout << "\n=======================================================\n";

	cout << "\n\nCompute total sightings\n";
	computeSum(sightings, totalSightings, noBirds);

	for (int index = 0; index < noBirds; index++)
		cout << "Total sightings for " << birds[index] << ": "
		<< totalSightings[index] << endl;
	cout << "\n=======================================================\n";

	cout << "\n\nFind the bird with the most sightings in a single area:\n";
	findBird(sightings, highestRow, highestCol, noBirds);
	cout << "\n\n" << birds[highestRow] << " had the highest sightings with "
		<< sightings[highestRow][highestCol] << endl;
	cout << "\n=======================================================\n";

	cout << "\n\nFind the most seen bird:\n";
	mostBirdsSeen(totalSightings, highestSighting, noBirds);
	cout << "\nMost seen bird is " << birds[highestSighting] << endl;

	cout << "\n=======================================================\n\n";
	printReport(fout, birds, sightings, totalSightings, highestSighting, noBirds);
	cout << "\n=======================================================\n\n";

	cout << "program ended successfully" << endl;
	cout << "\n\n Printing birds.dat file\n\n";
	system("type birds.dat");
	cout << "\n\n Printing birds.rpt file\n\n";
	system("type birds.rpt");
	system("pause");

}

//function to load paraelle arrays, with file passed as parameter, will return number of bird types
int loadArrays(ifstream& fin, string birdName[], int birdSightings[][LOCATION], int row)
{
	int col;

	// for loop to copy information from file to arrays, nested loop will load the 2d array
	for (row = 0; row < SIZE; row++)
	{
		if (fin.eof())
			break;
		getline(fin, birdName[row]);

		for (col = 0; col < LOCATION; col++)
		{
			fin >> birdSightings[row][col];
		}
		fin.ignore(80, '\n');
	}
	return row;
}

// Function that will add up the total sightings for each bird type
void computeSum(int sightings[][LOCATION], int totalSightings[], int& noBirds)
{
	int row, col;
	// do a for loop to add up sightings to get total sightings
	for (row = 0; row < noBirds; row++)
	{
		totalSightings[row] = 0;
		for (col = 0; col < LOCATION; col++)
		{
			totalSightings[row] += sightings[row][col];
		}
	}
}


void printReport(ofstream& fout, const string birdNames[], const int birdSightings[][LOCATION], int totalSightings[], int highestSightings, int numBirds)
{
	int row, col;

	fout << left << setw(25) << "Bird" << right << setw(25) << "Sightings" << endl;

	for (row = 0; row < numBirds; row++)
	{
		if (totalSightings[highestSightings] == totalSightings[row])
		{
			fout << left << setw(25) << birdNames[row] << ": ";
			for (col = 0; col < LOCATION; col++)
			{
				fout << right << setw(5) << birdSightings[row][col];
			}
			fout << setw(10) << totalSightings[row] << setw(40) << "*** Most Sightings ***" << endl;
		}
		else
		{
			fout << left << setw(25) << birdNames[row] << ": ";
			for (col = 0; col < LOCATION; col++)
			{
				fout << right << setw(5) << birdSightings[row][col];
			}
			fout << setw(10) << totalSightings[row] << endl;
		}
	}
	numBirds = row;
	fout << "\n\nThe number of birds: " << numBirds;

}

void findBird(int sightings[][LOCATION], int& highestRow, int& highestCol, int noBirds)
{
	int maxVal = sightings[0][0];
	int row, col;
	for (row = 0; row < noBirds; row++)
	{
		for (col = 0; col < LOCATION; col++)
		{
			if (sightings[row][col] > maxVal)
			{
				maxVal = sightings[row][col];
				highestRow = row;
				highestCol = col;
			}
		}
	}
}

// function to find the most viewed bird

void mostBirdsSeen(int totalSightings[], int& highestSighting, int noBirds)
{
	highestSighting = 0;
	int index;
	for (int index = 0; index < LOCATION; index++)
	{
		if (totalSightings[index] > highestSighting)
		{
			highestSighting = index;
		}
	}
}