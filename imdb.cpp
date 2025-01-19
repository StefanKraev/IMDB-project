#include <iostream>
#include <fstream>
const int SIZE = 50;
const uint8_t MMovieElements = 6;
const char file[18] = "MovieDatabase.txt";
const char fileC[22] = "CopyMovieDatabase.txt";

unsigned getLength(const char* text)
{
	if (!text)
		return 0;
	unsigned len = 0;
	while (*text != '\0')
	{
		len++;
		text++;
	}
	return len;
}

void stringCopy(char* copy, const char* original)
{
	if (!original || !copy)
		return;

	while (*original)
	{
		*copy = *original;
		copy++;
		original++;
	}

	*copy = '\0';
}

bool checkIfEqual(char* firstTxt, char* secondTxt)
{
	int lenFirst = getLength(firstTxt);
	int lenSecond = getLength(secondTxt);
	if (lenFirst != lenSecond)
		return false;
	while (*firstTxt != '\0')
	{
		if (*firstTxt != *secondTxt)
			return false;
		firstTxt++;
		secondTxt++;
	}
	return true;
}

bool hasGenre(char* genre, char* text)
{
	bool contains = true;
	unsigned lenGenre = getLength(genre);
	unsigned lenText = getLength(text);
	for (int i = 0; i <= lenText - lenGenre; i++)
	{
		contains = true;
		for (int j = 0; j < lenGenre; j++)
		{
			if (genre[j] != text[i])
			{
				contains = false;
				break;
			}
			else if (j == lenGenre - 1 && contains == true)
			{
				return true;
			}
			else
				i++;
		}
	}
	return false;
}

void fAppendStr(char str[])
{
	std::ofstream MyFile(file, std::ios::app);
	if (!MyFile.is_open()) return;
	MyFile << str << ' ';
	MyFile.close();
}

void fAppendInt(int rating)
{
	std::ofstream MyFile(file, std::ios::app);
	if (!MyFile.is_open()) return;
	MyFile << rating << ' ' << std::endl;
	MyFile.close();
}

void updateDatabase()
{
	std::ifstream MyFile(fileC);
	std::ofstream OutputFile(file);

	if (!MyFile.is_open())
		return;
	if (!OutputFile.is_open())
		return;

	while (!MyFile.eof())
	{
		char str[SIZE];
		MyFile.getline(str, SIZE);

		OutputFile << str << std::endl;
	}

	MyFile.close();
	OutputFile.close();
}

struct Movie
{
	char title[SIZE];
	char yearOfPublishing[SIZE];
	char genre[SIZE];
	char producer[SIZE];
	char actors[SIZE];
	unsigned rating;
};

void movieElements(const char* str, char movieElements[MMovieElements][SIZE])
{
	if (str[0] == '\0')
		return;
	int indexStr = 0;
	for (int i = 0; i < MMovieElements; i++)
	{
		int indexElement = 0;
		while (str[indexStr] != ' ')
		{
			movieElements[i][indexElement] = str[indexStr];
			indexStr++;
			indexElement++;
		}
		indexStr++;
	}
}

bool selectMovieByHeading(char* heading, char movieElements[MMovieElements][SIZE])
{
	int index = 0;
	char title[SIZE];
	while (movieElements[0][index])
	{
		title[index] = movieElements[0][index];
		index++;
	}
	title[index] = '\0';
	return checkIfEqual(heading, title);
}

void setMovieInput(Movie& movie, const char* input, char* element) 
{
	unsigned inputLength = getLength(input);
	if (inputLength < SIZE) {
		stringCopy(element, input);
	}
	else {
		std::cout << "Error: Input too long!" << std::endl;
	}
}

void addNewMovie()
{
	std::cout << "Please enter on each new line Title, Year of publishing, Genre, Producer and Actors:" << std::endl;
	Movie newMovie;

	char title[SIZE];
	std::cin >> title;

	setMovieInput(newMovie, title, newMovie.title);
	fAppendStr(newMovie.title);

	char yearOfPublishing[SIZE];
	std::cin >> yearOfPublishing;

	setMovieInput(newMovie, yearOfPublishing, newMovie.yearOfPublishing);
	fAppendStr(newMovie.yearOfPublishing);

	char genre[SIZE];
	std::cin >> genre;

	setMovieInput(newMovie, genre, newMovie.genre);
	fAppendStr(newMovie.genre);

	char producer[SIZE];
	std::cin >> producer;

	setMovieInput(newMovie, producer, newMovie.producer);
	fAppendStr(newMovie.producer);

	char actors[SIZE];
	std::cin >> actors;

	setMovieInput(newMovie, actors, newMovie.actors);
	fAppendStr(newMovie.actors);

	fAppendInt(5);

	std::cout << "movie successfully added!" << std::endl;
}

void searchByGenre(char* genre)
{
	std::ifstream MyFile(file);
	if (!MyFile.is_open())
		return;
	const size_t STRING_SIZE = 100;
	char str[STRING_SIZE];
	while (!MyFile.eof())
	{
		MyFile.getline(str, STRING_SIZE);
		
		bool containsGenre = hasGenre(genre, str);
		if (containsGenre)
			std::cout << str << std::endl;
	}

	MyFile.close();
}

void showAllMovies()
{
	std::ifstream MyFile(file);
	if (!MyFile.is_open())
		return;
	const size_t STRING_SIZE = 100;
	char str[STRING_SIZE];
	while (!MyFile.eof())
	{
		MyFile.getline(str, STRING_SIZE);

		std::cout << str << std::endl;
	}

	MyFile.close();
}

void editMovie(char* title)
{
	std::ifstream MyFile(file);

	if (!MyFile.is_open())
		return;

	std::ofstream OutputFile(fileC);

	if (!OutputFile.is_open())
		return;

	while (!MyFile.eof())
	{
		char str[SIZE];
		MyFile.getline(str, SIZE);

		char elements[MMovieElements][SIZE] = {};
		movieElements(str, elements);
		if (selectMovieByHeading(title, elements))
		{
			std::cout << "You want to edit the movie:" << str << std::endl;
			std::cout << "Please enter which element you want to change(genre, producer, etc.) and on the next line enter the new data" << std::endl;
			char answer[SIZE];
			std::cin >> answer;
			char newData[SIZE];
			std::cin >> newData;
			int index = 0;
			char year[] = "year_of_publishing";
			char genre[] = "genre";
			char producer[] = "producer";
			char actors[] = "actors";
			char rating[] = "rating";
			if (checkIfEqual(answer, year))
			{
				index = 1;
			}
			else if (checkIfEqual(answer, genre))
			{
				index = 2;
			}
			else if (checkIfEqual(answer, producer))
			{
				index = 3;
			}
			else if (checkIfEqual(answer, actors))
			{
				index = 4;
			}
			else if (checkIfEqual(answer, rating))
			{
				index = 5;
			}
			else
			{
				std::cout << "Invalid input" << std::endl;
				return;
			}

			char newLine[SIZE]{};
			int indexCopy = 0;
			unsigned num = 0;
			for (int i = 0; i <= 5; i++)
			{
				if (i == 5)
				{
					if (index == 5)
					{
						num = newData[0] - '0';
						if (newData[1] == '0')
							num *= 10;
						break;
					}
					else
					{
						newLine[indexCopy] = elements[5][0];
						newLine[indexCopy + 1] = ' ';
						break;
					}
				}
				int j = 0;
				while (elements[i][j] != '\0')
				{
					if (i == index)
					{
						while (newData[j] != '\0')
						{
							newLine[indexCopy] = newData[j];
							j++;
							indexCopy++;
						}
						break;
					}
					else
					{
						newLine[indexCopy] = elements[i][j];

						indexCopy++;
						j++;
					}
				}
				newLine[indexCopy] = ' ';
				indexCopy++;
			}
			if (index != 5)
			OutputFile << newLine << std::endl;
			else
			{
				OutputFile << newLine;
				OutputFile << num << ' ' << std::endl;
			}
		}
		else
			OutputFile << str << std::endl;
	}

	MyFile.close();
	OutputFile.close();
	updateDatabase();
}

void deleteMovie(char* title)
{
	std::ifstream MyFile(file);
	std::ofstream OutputFile(fileC);

	if (!MyFile.is_open())
		return;
	if (!OutputFile.is_open())
		return;

	while (!MyFile.eof())
	{
		char str[SIZE];
		MyFile.getline(str, SIZE);

		char elements[MMovieElements][SIZE] = {};
		movieElements(str, elements);
		if (selectMovieByHeading(title, elements))
		{
			std::cout << "Are you sure you want to delete the following movie:" << str << std::endl;
			bool answer;
			std::cin >> answer;
			if (answer) 
			{
				std::cout << "Movie successfully deleted!";
			}
			else
			{
				OutputFile << str << std::endl;
			}
		}
		else
		{
			OutputFile << str << std::endl;
		}
	}

	MyFile.close();
	OutputFile.close();
	updateDatabase();
}

void filterMovies()
{
	std::cout << "Please enter minimum rating" << std::endl;
	int minimumRating = 0;
	std::cin >> minimumRating;

	std::ifstream MyFile(file);

	if (!MyFile.is_open())
		return;

	while (!MyFile.eof())
	{
		char str[SIZE];
		MyFile.getline(str, SIZE);

		char elements[MMovieElements][SIZE] = {};
		movieElements(str, elements);
		if ((elements[5][0] - '0') >= minimumRating)
		{
			std::cout << str << std::endl;
		}
	}

	MyFile.close();
}

void sortMovies()
{
	std::cout << "Do you want to sort or filter the raings?" << std::endl;
	char answerr[SIZE];
	std::cin >> answerr;
	char filter[SIZE] = "filter";
	if (checkIfEqual(answerr, filter))
	{
		filterMovies();
		return;
	}

	std::ifstream MyFile(file);

	if (!MyFile.is_open())
		return;

	std::cout << "Do you want to sort the movies by rating or by title?" << std::endl;
	char rating[] = "rating";
	char title[] = "title";
	char answer[SIZE];
	std::cin >> answer;
	if (checkIfEqual(answer, rating))
	{
		int ratings[SIZE]{};
		int index = 0;
		while (!MyFile.eof())
		{
			char str[SIZE]{};
			MyFile.getline(str, SIZE);

			if (!str[0])
				continue;

			int i = 0;
			while (str[i + 2] != '\0')
				i++;
			if(str[i] == '0')
				ratings[index] = str[i] - '0' + 10;
			else
				ratings[index] = str[i] - '0';

			index++;
		}
		MyFile.close();

		for (size_t i = 0; i < index - 1; i++)
		{
			bool swapped = false;

			for (size_t j = 0; j < index - i - 1; j++)
			{
				if (ratings[j] > ratings[j + 1])
				{
					int copy = ratings[j];
					ratings[j] = ratings[j + 1];
					ratings[j + 1] = copy;
					swapped = true;
				}
			}

			if (!swapped)
			{
				break;
			}
		}

		std::ofstream OutputFile(fileC);

		if (!OutputFile.is_open())
			return;

		for (int j = 0; j < index; j++)
		{
			std::ifstream MyFile(file);

			if (!MyFile.is_open())
				return;

			while (!MyFile.eof())
			{
				char str[SIZE]{};
				MyFile.getline(str, SIZE);

				int currentNum = 0;
				int i = 0;
				while (str[i + 2] != '\0')
					i++;
				if (str[i] == '0')
					currentNum = str[i] - '0' + 10;
				else
					currentNum = str[i] - '0';

				if (currentNum == ratings[j])
				{
					OutputFile << str << std::endl;
				}
			}

			MyFile.close();
		}

		OutputFile.close();
	}
	else if (checkIfEqual(answer, title))
	{
		char headings[SIZE]{};
		int index = 0;
		while (!MyFile.eof())
		{
			char str[SIZE];
			MyFile.getline(str, SIZE);

			if (str[0] >= 'A' && str[0] <= 'Z')
			{
				headings[index] = str[0];
				index++;
			}
		}

		MyFile.close();

		for (size_t i = 0; i < index - 1; i++)
		{
			bool swapped = false;

			for (size_t j = 0; j < index - i - 1; j++)
			{
				if (headings[j] > headings[j + 1])
				{
					//swap(arr[j], arr[j + 1]);
					char copy = headings[j];
					headings[j] = headings[j + 1];
					headings[j + 1] = copy;

					swapped = true;
				}
			}

			if (!swapped)
			{
				break;
			}
		}

		std::ofstream OutputFile(fileC);

		if (!OutputFile.is_open())
			return;

		for (int j = 0; j < index; j++)
		{
			std::ifstream MyFile(file);

			if (!MyFile.is_open())
				return;

			while (!MyFile.eof())
			{
				char str[SIZE];
				MyFile.getline(str, SIZE);

				if (str[0] == headings[j])
				{
					OutputFile << str << std::endl;
				}
			}

			MyFile.close();
		}

		OutputFile.close();
	}
	else
	{
		std::cout << "Invalid Input!" << std::endl;
		MyFile.close();
	}

	updateDatabase();

	showAllMovies();
}

void rateMovie(char* title, int rating)
{
	std::ifstream MyFile(file);
	std::ofstream OutputFile(fileC);

	if (!MyFile.is_open())
		return;
	if (!OutputFile.is_open())
		return;

	if (rating < 1 || rating > 10)
	{
		std::cout << "Invalid rating" << std::endl;
		return;
	}

	while (!MyFile.eof())
	{
		char str[SIZE];
		MyFile.getline(str, SIZE);

		char elements[MMovieElements][SIZE] = {};
		movieElements(str, elements);
		if (selectMovieByHeading(title, elements))
		{
			int movieRating = (elements[5][0] + rating + '0')/2;
			char newRating = movieRating;
			
			char newLine[SIZE]{};
			int index = 0;
			while (str[index] != elements[5][0])
			{
				newLine[index] = str[index];
				index++;
			}
			newLine[index] = newRating;
			newLine[index + 1] = ' ';
			OutputFile << newLine << std::endl;
		}
		else
		{
			OutputFile << str << std::endl;
		}
	}

	MyFile.close();
	OutputFile.close();
	updateDatabase();
}

int main()
{
	bool admin = 0;
	std::cout << "Are you an administrator?" << std::endl;
	std::cin >> admin;
	std::cout << std::endl;
	
	std::cout << "Choose an option form the menu" << std::endl;
	if (admin)
		std::cout << "1. Add new movie" << std::endl;
	std::cout << "2. Search movie my heading" << std::endl;
	std::cout << "3. Search movie my genre" << std::endl;
	std::cout << "4. View all movies" << std::endl;
	if (admin)
		std::cout << "5. Edit movie" << std::endl;
	if (admin)
		std::cout << "6. Delete movie" << std::endl;
	std::cout << "7. Rate a movie" << std::endl;
	std::cout << "8. Sort and filter movie by rating" << std::endl;
	std::cout << "9. Exit the programm" << std::endl;

	int input = 0;
	std::cin >> input;
	switch (input)
	{
		case 1: 
			if (!admin)
			{
				std::cout << "Invalid input!";
				break;
			}
			addNewMovie();
			break;
		case 2:
			std::cout << "Please enter movie heading" << std::endl;
			char heading[SIZE];
			std::cin >> heading;
			searchByGenre(heading);
			break;
		case 3:
			std::cout << "Please enter movie genre" << std::endl;
			char genre[SIZE];
			std::cin >> genre;
			searchByGenre(genre);
			break;
		case 4:
			showAllMovies();
			break;
		case 5:
			if (!admin)
			{
				std::cout << "Invalid input!";
				break;
			}
			std::cout << "Please enter movie title" << std::endl;
			char title[SIZE];
			std::cin >> title;
			editMovie(title);
			break;

		case 6:
			if (!admin)
			{
				std::cout << "Invalid input!";
				break;
			}
			std::cout << "Please enter movie title" << std::endl;
			char ttitle[SIZE];
			std::cin >> ttitle;
			deleteMovie(ttitle);
			break;
		case 7:
			std::cout << "Please enter the movie you want to rate and on the next line your rating" << std::endl;
			char hheading[SIZE];
			int ratingg;
			std::cin >> hheading;
			std::cin >> ratingg;
			rateMovie(hheading, ratingg);
			break;
		case 8:
			sortMovies();
			break;
		case 9:
			break;
	}
}
