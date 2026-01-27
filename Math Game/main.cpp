#include <iostream>

using namespace std;

enum enQuestionLevel {Easy = 1, Med = 2, Hard = 3, Mix = 4};

enum enOperationType {Sum = 1, Sub = 2, Mul = 3, Div = 4, MixOp = 5 };

struct strQuestion
{
	short NumberOne = 0;
	short NumberTwo = 0;
	int CorrectAnswer = 0;
	int PlayerAnswer = 0;
	enQuestionLevel Level;
	enOperationType OpType;
	bool IsCorrect = false;
};

struct strQuizz
{
	strQuestion Questions[100];
	short NumberOfQuestions = 0;
	short NumberOfRightAnswers = 0;
	short NumberOfWrongAnswers = 0;
	enQuestionLevel Level;
	enOperationType OpType;
	bool IsPass = false;
};

int RandomNumber(int From, int To)
{
	int RandNum = rand() % (To - From + 1) + From;
	return RandNum;
}

void ResetScreen()
{
	system("cls");
	system("color 0F");
}

string Tabs(short NumberOfTabs)
{
	string T;

	for (short i = 1; i <= NumberOfTabs; i++)
	{
		T += "\t";
	}
	return T;
}

string GetOperationTypeSymbol(enOperationType OpType)
{
	switch (OpType)
	{
		case enOperationType::Sum:
		{
			return "+";
			break;
		}
		case enOperationType::Sub:
		{
			return "-";
			break;
		}
		case enOperationType::Mul:
		{
			return "*";
			break;
		}
		case enOperationType::Div:
		{
			return "/";
			break;
		}
		default:
		{
			return "Mix";
			break;
		}
	}
}

string GetQuestionsLevelText(enQuestionLevel Level)
{
	string Levels[4] = {"Easy", "Med", "Hard", "Mix"};
	return Levels[Level - 1];
}

short ReadNumberOfQuestions()
{
	short NumberOfQuestions = 0;

	cout << "How Many Questions Do You Want To Answer? (1 To 100)\n";
	cin >> NumberOfQuestions;

	while (cin.fail() || NumberOfQuestions < 1 || NumberOfQuestions > 100)
	{
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		cout << "Invalid Input, Enter A Number Between 1 And 100: ";
		cin >> NumberOfQuestions;
	}

	return NumberOfQuestions;
}

enQuestionLevel ReadQuestionsLevel()
{
	short QuestionsLevel = 0;

	cout << "\nEnter Questions Level: 1) Easy 2) Med 3) Hard 4) Mix\n";
	cin >> QuestionsLevel;

	while (cin.fail() || QuestionsLevel < 1 || QuestionsLevel > 4)
	{
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		cout << "Invalid Input, Enter A Number Between 1 And 4: ";
		cin >> QuestionsLevel;
	}

	return (enQuestionLevel)QuestionsLevel;
}

enOperationType ReadOperationType()
{
	short OperationType = 0;

	cout << "\nEnter Operation Type: 1) Sum 2) Sub 3) Mul 4) Div 5) Mix\n";
	cin >> OperationType;

	while (cin.fail() || OperationType < 1 || OperationType > 5)
	{
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		cout << "Invalid Input, Enter A Number Between 1 And 5: ";
		cin >> OperationType;
	}

	return (enOperationType)OperationType;
}

int SimpleCalculator(short NumberOne, short NumberTwo, enOperationType OpType)
{
	switch (OpType)
	{
		case enOperationType::Sum:
		{
			return NumberOne + NumberTwo;
			break;
		}

		case enOperationType::Sub:
		{
			return NumberOne - NumberTwo;
			break;
		}

		case enOperationType::Mul:
		{
			return NumberOne * NumberTwo;
			break;
		}

		case enOperationType::Div:
		{
			return NumberOne / NumberTwo;
			break;
		}

		default:
		{
			return NumberOne + NumberTwo;
			break;
		}
	}

}

strQuestion GenerateQuestion(enQuestionLevel Level, enOperationType OpType)
{
	strQuestion Question;

	if (Level == enQuestionLevel::Mix)
	{
		Level = (enQuestionLevel)RandomNumber(1, 3);
	}

	if (OpType == enOperationType::MixOp)
	{
		OpType = (enOperationType)RandomNumber(1, 4);
	}

	Question.Level = Level;
	Question.OpType = OpType;

	switch (Level)
	{
		case enQuestionLevel::Easy:
		{
			Question.NumberOne = RandomNumber(1, 10);
			Question.NumberTwo = RandomNumber(1, 10);
			Question.CorrectAnswer = SimpleCalculator(Question.NumberOne, Question.NumberTwo, Question.OpType);
			break;
		}

		case enQuestionLevel::Med:
		{
			Question.NumberOne = RandomNumber(10, 50);
			Question.NumberTwo = RandomNumber(10, 50);
			Question.CorrectAnswer = SimpleCalculator(Question.NumberOne, Question.NumberTwo, Question.OpType);
			break;
		}

		case enQuestionLevel::Hard:
		{
			Question.NumberOne = RandomNumber(50, 100);
			Question.NumberTwo = RandomNumber(50, 100);
			Question.CorrectAnswer = SimpleCalculator(Question.NumberOne, Question.NumberTwo, Question.OpType);
			break;
		}
	}

	return Question;
}

void GenerateQuestions(strQuizz &Quizz)
{
	for (short QuestionNumber = 0; QuestionNumber < Quizz.NumberOfQuestions; QuestionNumber++)
	{
		Quizz.Questions[QuestionNumber] = GenerateQuestion(Quizz.Level, Quizz.OpType);
	}
}

int ReadPlayerAnswer()
{
	int Answer;
	cin >> Answer;

	while (cin.fail())
	{
		cout << "Invalid Input, Enter A Number: ";
		cin >> Answer;
	}

	return Answer;
}

void PrintTheQuestion(strQuizz Quizz, short QuestionNumber)
{
	cout << "\nQuestion [" << QuestionNumber + 1 << "/" << Quizz.NumberOfQuestions << "]\n\n";
	cout << Quizz.Questions[QuestionNumber].NumberOne << "\n";
	cout << Quizz.Questions[QuestionNumber].NumberTwo << " " << GetOperationTypeSymbol(Quizz.Questions[QuestionNumber].OpType);
	cout << "\n----------------\n";
}

void SetScreenColor(bool Right)
{
	if (Right)
		system("color 2F");

	else
	{
		system("color 4F");
		cout << "\a";
	}

}

void CorrectTheAnswer(strQuizz &Quizz, short QuestionNumber)
{
	if (Quizz.Questions[QuestionNumber].CorrectAnswer == Quizz.Questions[QuestionNumber].PlayerAnswer)
	{
		cout << "\nRigth Answer :-)\n";
		Quizz.NumberOfRightAnswers++;
		Quizz.Questions[QuestionNumber].IsCorrect = true;
	}

	else
	{
		cout << "\nWrong Answer :-(\n";
		cout << "The Right Answer Is: " << Quizz.Questions[QuestionNumber].CorrectAnswer << endl;
		Quizz.NumberOfWrongAnswers++;
		Quizz.Questions[QuestionNumber].IsCorrect = false;
	}

	SetScreenColor(Quizz.Questions[QuestionNumber].IsCorrect);
}

void AnswerAndCorrectTheQuestions(strQuizz& Quizz)
{
	for (short QuestionNumber = 0; QuestionNumber < Quizz.NumberOfQuestions; QuestionNumber++)
	{
		PrintTheQuestion(Quizz, QuestionNumber);
		Quizz.Questions[QuestionNumber].PlayerAnswer = ReadPlayerAnswer();
		CorrectTheAnswer(Quizz, QuestionNumber);
	}

	Quizz.IsPass = (Quizz.NumberOfRightAnswers >= Quizz.NumberOfWrongAnswers);

}

string GetFinalResultText(bool IsPass)
{
	if (IsPass)
		return "Pass :-)";
	else
		return "Fail :-(";
}

void PrintQuizzResult(strQuizz Quizz)
{
	cout << endl;
	cout << Tabs(4) << "--------------------------------------\n";
	cout << Tabs(5) << "Final Result Is: " << GetFinalResultText(Quizz.IsPass) << endl;
	cout << Tabs(4) << "--------------------------------------\n";
	cout << Tabs(4) << "Number Of Questions      : " << Quizz.NumberOfQuestions << endl;
	cout << Tabs(4) << "Questions Level          : " << GetQuestionsLevelText(Quizz.Level) << endl;
	cout << Tabs(4) << "Operation Type           : " << GetOperationTypeSymbol(Quizz.OpType) << endl;
	cout << Tabs(4) << "Number Of Right Questions: " << Quizz.NumberOfRightAnswers << endl;
	cout << Tabs(4) << "Number Of Wrong Questions: " << Quizz.NumberOfWrongAnswers << endl;
	cout << Tabs(4) << "--------------------------------------\n";
	SetScreenColor(Quizz.IsPass);
}

void PlayGame()
{
	strQuizz Quizz;

	Quizz.NumberOfQuestions = ReadNumberOfQuestions();
	Quizz.Level = ReadQuestionsLevel();
	Quizz.OpType = ReadOperationType();

	GenerateQuestions(Quizz);
	AnswerAndCorrectTheQuestions(Quizz);
	PrintQuizzResult(Quizz);
}

void StartGame()
{
	char PlayAgain = 'Y';

	do
	{
		ResetScreen();
		PlayGame();

		cout << Tabs(4) << "Do You Want To Play Again? (Y/N)";
		cin >> PlayAgain;

	} while (toupper(PlayAgain) == 'Y');
}

int main()
{
	srand((unsigned)time(NULL));

	StartGame();

	return 0;
}