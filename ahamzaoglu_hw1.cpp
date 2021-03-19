//Alpaslan Hamzaoglu

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;


// printing the vector of integer vector
void print_matrix(const vector<vector<int> > board_matrix)
{
	cout << "Files are in correct format" << endl;

	for (int i = 1; i < board_matrix.size(); i++)
	{
		for (int h = 0; h < board_matrix[i].size(); h++)
		{
			cout << board_matrix[i][h] << " ";
		}

		cout << endl;
	}
}


// find out that is there still X's which has not answer yet in board
bool is_there_x(const vector<vector<int> > board_matrix)
{
	for (int i = 1; i < board_matrix.size(); i++)
	{
		for (int h = 0; h < board_matrix[i].size(); h++)
		{
			if (board_matrix[i][h] == 0)
			{
				return true;
			}
		}
	}

	return false;
}


// checking X in a row and find correct value for it
void find_x_row(vector<vector<int> >& board_matrix)
{
	int count = 0, sequence = 0, index = 0, board_size = board_matrix[0][0];

	for (int i = 1; i < board_matrix.size(); i++)
	{
		for (int h = 0; h < board_matrix[i].size(); h++)
		{
			if (board_matrix[i][h] == 0)
			{
				count++;
				index = h;
			}

			else
			{
				sequence += board_matrix[i][h];
			}
		}

		if (count == 1)
		{
			board_matrix[i][index] = ((board_size * (board_size + 1)) / 2) - sequence;		// (n*(n+1)) / 2 --> it is general formula 1 to n sequence sum
		}

		sequence = 0;
		count = 0;
	}
}


// checking x in a column and find correct value for it
void find_x_column(vector<vector<int> >& board_matrix)
{
	int index = 0, count = 0, sequence = 0, board_size = board_matrix[0][0];

	for (int i = 0; i < board_matrix[i].size(); i++)
	{
		for (int h = 1; h < board_matrix.size(); h++)
		{
			if (board_matrix[h][i] == 0)
			{
				count++;
				index = h;
			}

			else
			{
				sequence += board_matrix[h][i];
			}
		}

		if (count == 1)
		{
			board_matrix[index][i] = ((board_size * (board_size + 1)) / 2) - sequence;		// (n*(n+1)) / 2 --> it is general formula 1 to n sequence sum                  
		}

		sequence = 0;
		count = 0;
	}
}


// finding a suitable value for X's
void x_finder(bool &check, vector<vector<int> >& board_matrix, const vector<vector<int> > constraint_matrix)
{
	int borad_size = board_matrix[0][0], count = 0;


	// trying to find a value for X's without checking constraint matrix
	for (int i = 0; i < borad_size; i++)
	{
		find_x_row(board_matrix);
		find_x_column(board_matrix);
	}
	

	// if there is no X has left so it stop and go to print the board 
	if (!is_there_x(board_matrix))
	{
		check = true;
		return;
	} 


	// if there is still X's then it is checking the constraint matrix and try to find a valur for X's
	for (int i = 1; i < constraint_matrix.size(); i++)
	{
		if (board_matrix[constraint_matrix[i][0]][constraint_matrix[i][1] - 1] == 0 && board_matrix[constraint_matrix[i][2]][constraint_matrix[i][3] - 1] == 0)
		{
			continue;
		}

		else if (board_matrix[constraint_matrix[i][0]][constraint_matrix[i][1] - 1] == 0)
		{
			count = 0;

			for (int h = 1; h <= borad_size; h++)
			{
				if (board_matrix[constraint_matrix[i][2]][constraint_matrix[i][3] - 1] < h)
				{
					count++;
				}
			}
			if (count == 1)
			{
				board_matrix[constraint_matrix[i][0]][constraint_matrix[i][1] - 1] = borad_size;
			}
		}

		else if (board_matrix[constraint_matrix[i][2]][constraint_matrix[i][3] - 1] == 0)
		{
			count = 0;

			for (int h = 1; h <= borad_size; h++)
			{
				if (board_matrix[constraint_matrix[i][0]][constraint_matrix[i][1]] < h)
				{
					count++;
				}

				if (count == 1)
				{
					board_matrix[constraint_matrix[i][2]][constraint_matrix[i][3] - 1] = borad_size;
				}
			}
		}
	}


	// if there is still X's, checking finally trying to find a value for X's without checking constraint matrix
	for (int i = 0; i < borad_size; i++)
	{
		find_x_row(board_matrix);
		find_x_column(board_matrix);
	}


	// if there still X's then it is going to print warning
	if (is_there_x(board_matrix))
	{
		check = false;
		cout << "X's can have more than 1 value" << endl;
		return;
	}

	check = true;
}


// checking the board and constraint, are they hold each other
bool check_board_constraint(const vector<vector<int> > board_matrix, const vector<vector<int> > constraint_matrix)
{
	for (int i = 1; i < constraint_matrix.size(); i++)
	{
		if (board_matrix[constraint_matrix[i][0]][constraint_matrix[i][1]-1] == 0 || board_matrix[constraint_matrix[i][2]][constraint_matrix[i][3]-1] == 0)
		{
			continue;
		}

		else if (board_matrix[constraint_matrix[i][0]][constraint_matrix[i][1]-1] <= board_matrix[constraint_matrix[i][2]][constraint_matrix[i][3]-1])
		{
			return false;
		}	
	}

	return true;
}


// converting string vector of board and constraint to vector of integer vector and checking are the values correct 
void converter_and_checker(bool &check, const vector<string> board_vector, const vector<string> constraint_vector, vector<vector<int> >& board_matrix, vector<vector<int> >& constraint_matrix)
{
	int board_size = stoi(board_vector[0]), constraint_size = stoi(constraint_vector[0]);  
	string repeating = "";																		        // assigning repeating string to find a repetition in board 

	
	// checking first row the string vector and add board maxtrix 
	for (int i = 0; i < board_vector[0].size();)													
	{
		if (!(('0' <= board_vector[0][i] && board_vector[0][i] <= '9') || board_vector[0][i] == ' '))
		{
			check = false;
			return;
		}

		else if (i == 0)
		{
			int find = board_vector[0].find(" ");

			if (find = -1)
			{
				board_matrix[0].push_back(stoi(board_vector[0]));

				i += board_vector[0].length();
			}

			else
			{
				board_matrix[0].push_back(stoi(board_vector[0].substr(0, find)));
				board_vector[0].substr(find, board_vector[0].size());

				i += find;
			}
			
		}

		else if (board_vector[0][i] != ' ')
		{
			check = false;
			return;
		}
	}


	// // checking first row the string vector and add constraint matrix
	for (int i = 0; i < constraint_vector[0].size();)														
	{
		if (!(('0' <= constraint_vector[0][i] && constraint_vector[0][i] <= '9') || constraint_vector[0][i] == ' '))
		{
			check = false;
			return;
		}

		else if (i == 0)
		{
			int find = constraint_vector[0].find(" ");

			if (find == -1)
			{
				constraint_matrix[0].push_back(stoi(constraint_vector[0]));

				i += constraint_vector[0].length();
			}

			else
			{
				constraint_matrix[0].push_back(stoi(constraint_vector[0].substr(0, find)));
				constraint_vector[0].substr(find, constraint_vector[0].length());

				i += find;
			}
			
		}

		else if (constraint_vector[0][i] != ' ')
		{
			check = false;
			return;
		}
	}


	// checking and converting string board to vector of integer vector board
	for (int i = 1; i < board_vector.size() && i < board_matrix.size(); i++)
	{
		for (int h = 0; h < board_vector[i].size(); h++)
		{
			if (board_vector[i][h] != 'X' && board_vector[i][h] != ' ' && !('0' <= board_vector[i][h] && board_vector[i][h] <= '9'))
			{
				check = false;
				return;
			}

			else if (board_vector[i][h] == ' ')
			{
				continue;
			}

			else if (board_vector[i][h] == 'X')
			{
				board_matrix[i].push_back(0);
			}

			else if (!(0 < int(board_vector[i][h] - '0') && int(board_vector[i][h] - '0') <= board_size))
			{
				cout << "Value " << board_vector[i][h] << " is out of matrix size" << endl;
				check = false;
				return;
			}

			else
			{
				int find = board_vector[i].find(' ');

				if (find == -1)
				{
					board_matrix[i].push_back(int(board_vector[i][h]-'0'));
				}

				else
				{
					board_matrix[i].push_back(stoi(board_vector[i].substr(h, find)));
				}
			}
		}
	}


	// checking and converting string constraint to vector of integer vector constraint
	for (int i = 1; i < constraint_vector.size() && i < constraint_matrix.size(); i++)
	{
		for (int h = 0; h < constraint_vector[i].size(); h++)
		{
			if (constraint_vector[i][h] != ' ' && !('0' <= constraint_vector[i][h] && constraint_vector[i][h] <= '9'))
			{
				check = false;
				return;
			}

			else if (constraint_vector[i][h] == ' ')
			{
				continue;
			}

			else if (!(0 < int(constraint_vector[i][h]-'0') && int(constraint_vector[i][h]-'0') <= constraint_size))
			{
				cout << "Value " << constraint_vector[i][h] << " is out of matrix size" << endl;
				check = false;
				return;
			}			

			else
			{
				int find = constraint_vector[i].find(' ');

				if (find == -1)
				{
					constraint_matrix[i].push_back(int(constraint_vector[i][h] - '0'));
				}

				else
				{
					constraint_matrix[i].push_back(stoi(constraint_vector[i].substr(h, find)));
				}
			}
		}
	}


	// checking board size is it correct
	if (board_vector.size() != board_size + 1)
	{
		cout << "File contains more lines than size" << endl;
		check = false;
		return;
	}


	// checking the constraint size is it correct
	else if (constraint_vector.size() != constraint_size + 1)
	{
		cout << "There are more constraints then previously stated" << endl;
		check = false;
		return;
	}


	// finding a repetition in same row
	for (int i = 1; i < board_matrix.size(); i++)
	{
		for (int h = 0; h < board_matrix[i].size(); h++)
		{
			for (int g = h+1; g < board_matrix[i].size(); g++)
			{
				if (board_matrix[i][h] == 0 || board_matrix[i][g] == 0)
				{
					continue;
				}

				else if (board_matrix[i][h] == board_matrix[i][g])
				{
					cout << "There is a value repeating in same row" << endl;
					check = false;
					return;
				}
			}
		}
	}


	// find a repetition in same column
	for (int i = 0; i < board_matrix[i].size(); i++)
	{
		for (int h = 1; h < board_matrix.size()-1; h++)
		{
			for (int g = h + 1; g < board_matrix[i].size(); g++)
			{
				if (board_matrix[h][i] == 0 || board_matrix[g][i] == 0)
				{
					continue;
				}

				else if ((board_matrix[h][i] == board_matrix[g][i]))
				{						
					cout << "There is a value repeating in same column" << endl;
					check = false;
					return;
				}
			}			
		}
	}


	// checking the constraint matrix that are they match with board matrix
	if (!check_board_constraint(board_matrix, constraint_matrix))
	{
		cout << "Constraints do not match board" << endl;
		check = false;
		return;
	}
}


// opening folders and writing the values in string vector
void folders(vector<string>& board_vector, vector<string>& constraint_vector)
{
	string board_str, constraint_str, line_board, line_constraint;
	ifstream board_file, constraint_file;

	cout << "Enter the board file: ";
	cin >> board_str;													// getting name of board file

	cout << "Enter the constraint file: ";								// getting name of constraint file
	cin >> constraint_str;

	board_file.open(board_str);											// opening the both of them
	constraint_file.open(constraint_str);

	if (constraint_file.fail())											// checking is it opened
	{
		return;
	}

	while (getline(board_file, line_board))								// reading the board file
	{
		if (!line_board.empty())
		{
			board_vector.push_back(line_board);
		}
	}

	while (getline(constraint_file, line_constraint))					// reading the constraint file
	{
		if (!line_constraint.empty())
		{
			constraint_vector.push_back(line_constraint);
		}
	}

	board_file.close();													// closing the both of them
	constraint_file.close();
}


// main function
int main()
{
	bool check = true;																							// assigning bool variable to check 

	vector<string> board_vector;																				// assigning string vector for board file
	vector<string> constraint_vector;																			// assigning string vector for constraint file

	folders(board_vector, constraint_vector);																	// opening folders and writing the values in string vector
																											

	if (board_vector.size() != 0 && constraint_vector.size() != 0)                                   			// checking size of string vector of board and constraint
	{
		if (stoi(board_vector[0]) != -1 && stoi(constraint_vector[0]) != -1)									// checking first element of files is it correct
		{
			vector<vector<int> > board_matrix(stoi(board_vector[0]) + 1);										// assigning vector of integer vector for board file
			vector<vector<int> > constraint_matrix(stoi(constraint_vector[0]) + 1);								// assigning vector of integer vector for constraint file

			converter_and_checker(check, board_vector, constraint_vector, board_matrix, constraint_matrix);		// converting string vector of board and constraint to vector of integer vector 
																												// and checking are the values correct 

			if (check)
			{
				x_finder(check, board_matrix, constraint_matrix);												// finding a suitable value for X's
			
				if (check)
				{
					print_matrix(board_matrix);																	// printing the vector of integer vector	
				}
			}
		}
		
	}
	
	return 0;
}