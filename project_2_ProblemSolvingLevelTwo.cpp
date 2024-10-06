/*                         Project Number Two                             dec 2, 2023 */

#include <iostream>
#include <cstdlib>
using namespace std;


enum enQuizLevel { Easy = 1, Mid, Hard, MMix };
enum enOperType { Add = 1, Sub, Mul, Div, Mix };

struct stQuestionInfo {
	short QuestionNumber;
	short Num1;
	short Num2;
	enOperType OperType;
	int UserAnswer;
	int RightAnswer;
};

struct stQuizData
{
	short NumOfQuestions = 0;
	string QuizLevel;
	string OperationType;
	short NumOfWin;
	short NumOfLose;
};

int ReadNumberInRange(int From, int To, string Message)
{
	int Number;
	do
	{
		cout << Message;
		cin >> Number;
	} while (Number < From || Number > To);
	return Number;
}

int RandomNumber(int From, int To)
{
	return rand() % (To - From + 1) + From;
}

void ResetScreen()
{
	system("cls");
	system("color 0F");
}

int ReadQuestionsNumber()
{
	return ReadNumberInRange(1, 10, "How many questions do want to answer: ");
}

enQuizLevel ReadQuizLevel()
{
	return enQuizLevel(ReadNumberInRange(1, 4, "Enter Questions level [1]Easy [2]Mid [3]Hard [4]Mix:  "));
}

enOperType ReadOperType()
{
	return enOperType(ReadNumberInRange(1, 5, "Enter operation type [1]Add, [2]Sub, [3]Mul, [4]Div, [5]Mix:  "));
}

int GetRandomNumberAccordingToGameLevel(enQuizLevel QuizLevel)
{
	switch (QuizLevel)
	{
	case enQuizLevel::Easy:
		return RandomNumber(1, 10);
	case enQuizLevel::Mid:
		return RandomNumber(11, 50);
	case enQuizLevel::Hard:
		return RandomNumber(51, 100);
	default:
		return RandomNumber(1, 100);
	}
}

enOperType GetRandomOperType(enOperType OperType)
{
	if (OperType == enOperType::Mix)
		return (enOperType)RandomNumber(1, 4);
	else
		return OperType;
}

int GetRightAnswer(stQuestionInfo QuestInfo)
{
	switch (QuestInfo.OperType)
	{
	case enOperType::Add:
		return QuestInfo.Num1 + QuestInfo.Num2;
	case enOperType::Sub:
		return QuestInfo.Num1 - QuestInfo.Num2;
	case enOperType::Mul:
		return QuestInfo.Num1 * QuestInfo.Num2;
	case enOperType::Div:
		return QuestInfo.Num1 / QuestInfo.Num2;
	}
}

string GetOper(enOperType OperType)
{
	string Oper[5] = { "+", "-", "*", "/", "Mix" };
	return Oper[OperType - 1];
}

string GetQuizLevel(enQuizLevel QuizLevel)
{
	string Level[4] = { "Easy", "Mid", "Hard", "Mix" };
	return Level[QuizLevel - 1];
}

int GetUserAnswer(stQuestionInfo QuestionInfo, int NumberOfQues)
{
	int Answer = 0;
	cout << "\n\nQuestion [" << QuestionInfo.QuestionNumber << "/" << NumberOfQues << "]\n";
	cout << QuestionInfo.Num1 << endl;
	cout << QuestionInfo.Num2  << " " << GetOper(QuestionInfo.OperType) << endl;
	cout << "__________________\n";
	cin >> Answer;
	return Answer;
}

void PrintQuestionResults(stQuestionInfo QuestionInfo)
{
	if (QuestionInfo.RightAnswer == QuestionInfo.UserAnswer)
	{
		system("color 2F");
		cout << "\nRight Answer :-)\n";
	}
	else
	{
		system("color 4F");
		cout << "\a\nWrong Answer :-(\n";
		cout << "The right Answer is " << QuestionInfo.RightAnswer << endl;
	}
}

stQuizData ReturnQuizData(short NumOfQuiz, enQuizLevel QuizLevel, enOperType OperType, short NumOfWin, short NumOfLose)
{
	stQuizData Data;
	Data.NumOfQuestions = NumOfQuiz;
	Data.QuizLevel = GetQuizLevel(QuizLevel);
	Data.OperationType = GetOper(OperType);
	Data.NumOfWin = NumOfWin;
	Data.NumOfLose = NumOfLose;

	return Data;
}

stQuizData StartQuestions(int NumberOfQues)
{
	enQuizLevel QuizLevel = ReadQuizLevel();
	enOperType OperType = ReadOperType();

	stQuestionInfo QuestionInfo;
	int NumOfWin = 0, NumOfLose = 0;
	for (int QuestNum = 1; QuestNum <= NumberOfQues; QuestNum++)
	{
		QuestionInfo.QuestionNumber = QuestNum;
		QuestionInfo.Num1 = GetRandomNumberAccordingToGameLevel(QuizLevel);
		QuestionInfo.Num2 = GetRandomNumberAccordingToGameLevel(QuizLevel);
		QuestionInfo.OperType = GetRandomOperType(OperType);
		QuestionInfo.RightAnswer = GetRightAnswer(QuestionInfo);
		QuestionInfo.UserAnswer = GetUserAnswer(QuestionInfo, NumberOfQues);
		PrintQuestionResults(QuestionInfo);

		if (QuestionInfo.RightAnswer == QuestionInfo.UserAnswer)
			NumOfWin++;
		else
			NumOfLose++;
	}
	return ReturnQuizData(NumberOfQues, QuizLevel, OperType, NumOfWin, NumOfLose);
}

void PrintResultsHeader(short NumOfWin, short NumOfLose)
{
	if (NumOfWin > NumOfLose)
	{
		cout << "\n\n______________________________\n\n";
		cout << "The final result is Pass :-)";
		system("color 2F");
	}
	else
	{
		cout << "\n\n______________________________\n\n";
		cout << "The final result is Fail :-(\a";
		system("color 4F");
	}

}

void PrintQuizResults(stQuizData QuizResults)
{
	PrintResultsHeader(QuizResults.NumOfWin, QuizResults.NumOfLose);
	cout << "\n______________________________\n\n";
	cout << "Number of questions     : " << QuizResults.NumOfQuestions;
	cout << "\nQuestions' level        : " << QuizResults.QuizLevel;
	cout << "\nOperator Type           : " << QuizResults.OperationType;
	cout << "\nNumber of right answers : " << QuizResults.NumOfWin;
	cout << "\nNumber of wrong answers : " << QuizResults.NumOfLose;
	cout << "\n______________________________\n";
}


void StartProject()
{
	stQuizData QuizResults;
	char PlayAgain = 'Y';
	do
	{
		ResetScreen();
		QuizResults = StartQuestions(ReadQuestionsNumber());

		PrintQuizResults(QuizResults);

		cout << "\nDo want to play again Y/N: ";
		cin >> PlayAgain;
	} while (PlayAgain == 'y' || PlayAgain == 'Y');

}

int main()
{
	srand((unsigned)time(NULL));

	StartProject();

}


