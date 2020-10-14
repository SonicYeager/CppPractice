#include "gtest/gtest.h"
#include "BowlingGame.h"


class GameMock : public Bowling::Game
{
public:
	void SetHistory(std::vector<Bowling::Frame> his)
	{
		this->history = his;
	}
};


TEST(TestGame, History_EmptyInstance_ReturnEmptyHistory)
{
	auto actual = Bowling::Game{};
	auto actualHistory = actual.History();
	auto expectHistory = std::vector<Bowling::Frame>{};
	EXPECT_EQ(actualHistory, expectHistory);
}

TEST(TestGame, Score_EmptyInstance_ReturnZero)
{
	auto actual = Bowling::Game{};
	auto actualScore = actual.Score();
	auto expectScore = 0;
	EXPECT_EQ(actualScore, expectScore);
}

TEST(TestGame, Score_ModifiedInstance_ReturnModifiedScore)
{
	auto actual = GameMock{};

	actual.SetHistory(std::vector<Bowling::Frame>{ { {2, 4}, 6 }});

	auto actualScore = actual.Score();
	auto expectScore = 6;
	EXPECT_EQ(actualScore, expectScore);
}

TEST(TestGame, Roll_OnePin_SetHistoryAndScoreToOne)
{
	auto actual = Bowling::Game{};
	actual.Roll(1);
	auto actualHistory = actual.History();
	auto actualScore = actual.Score();
	auto expectHistory = std::vector<Bowling::Frame>{ { {1}, 1 } };
	auto expectScore = 1;

	EXPECT_EQ(actualHistory, expectHistory);
	EXPECT_EQ(actualScore, expectScore);
}

TEST(TestGame, Roll_TwoRollsOnePin_SetHistoryAndScore)
{
	auto actual = Bowling::Game{};
	actual.Roll(1);
	actual.Roll(1);
	auto actualHistory = actual.History();
	auto actualScore = actual.Score();
	auto expectHistory = std::vector<Bowling::Frame>{ { {1, 1}, 2 } };
	auto expectScore = 2;

	EXPECT_EQ(actualHistory, expectHistory);
	EXPECT_EQ(actualScore, expectScore);
}

TEST(TestGame, Roll_ThreeRollsMultiplePin_SetHistoryAndScore)
{
	auto actual = Bowling::Game{};
	actual.Roll(2);
	actual.Roll(3);
	actual.Roll(3);
	auto actualHistory = actual.History();
	auto actualScore = actual.Score();
	auto expectHistory = std::vector<Bowling::Frame>{ { {2, 3}, 5 }, {{3}, 3} };
	auto expectScore = 8;

	EXPECT_EQ(actualHistory, expectHistory);
	EXPECT_EQ(actualScore, expectScore);
}

TEST(TestGame, Roll_AnotherRoundAfterSpare_AddBonus)
{
	auto actual = Bowling::Game{};
	actual.Roll(7);
	actual.Roll(3);
	actual.Roll(3);
	actual.Roll(4);
	auto actualHistory = actual.History();
	auto actualScore = actual.Score();
	auto expectHistory = std::vector<Bowling::Frame>{ { {7, 3}, 13 }, {{3, 4}, 7} };
	auto expectScore = 20;

	EXPECT_EQ(actualHistory, expectHistory);
	EXPECT_EQ(actualScore, expectScore);
}

TEST(TestGame, Roll_TwoAnotherRoundAfterStrike_AddBonus)
{
	auto actual = Bowling::Game{};
		
	actual.Roll(10);
	actual.Roll(3);
	actual.Roll(5);
	actual.Roll(1);

	auto actualHistory = actual.History();
	auto actualScore = actual.Score();
	auto expectHistory = std::vector<Bowling::Frame>{ { {10}, 18 }, {{3, 5}, 8}, {{1}, 1} };
	auto expectScore = 27;
	EXPECT_EQ(actualHistory, expectHistory);
	EXPECT_EQ(actualScore, expectScore);
}

TEST(TestGame, Roll_SpareLastRound_3RollsLastRound)
{
	auto actual = Bowling::Game{};

	actual.Roll(1);
	actual.Roll(4);
	actual.Roll(4);
	actual.Roll(5);
	actual.Roll(6);
	actual.Roll(4);
	actual.Roll(5);
	actual.Roll(5);
	actual.Roll(10);
	actual.Roll(0);
	actual.Roll(1);
	actual.Roll(7);
	actual.Roll(3);
	actual.Roll(6);
	actual.Roll(4);
	actual.Roll(10);
	actual.Roll(2);
	actual.Roll(8);
	actual.Roll(6);

	auto actualHistory = actual.History();
	auto actualScore = actual.Score();
	auto expectHistory = std::vector<Bowling::Frame>{ { {1, 4}, 5 }, {{4, 5}, 9}, {{6, 4}, 15}, {{5, 5}, 20}, {{10}, 11}, {{0, 1}, 1}, {{7, 3}, 16}, {{6, 4}, 20}, {{10}, 20}, {{2, 8, 6}, 16}};
	auto expectScore = 133;
	EXPECT_EQ(actualHistory, expectHistory);
	EXPECT_EQ(actualScore, expectScore);
}

TEST(TestGame, Roll_SpareLastRound_3RollsLastRound)
{
	auto actual = Bowling::Game{};

	actual.Roll(1);
	actual.Roll(4);
	actual.Roll(4);
	actual.Roll(5);
	actual.Roll(6);
	actual.Roll(4);
	actual.Roll(5);
	actual.Roll(5);
	actual.Roll(10);
	actual.Roll(0);
	actual.Roll(1);
	actual.Roll(7);
	actual.Roll(3);
	actual.Roll(6);
	actual.Roll(4);
	actual.Roll(10);
	actual.Roll(10);
	actual.Roll(6);
	actual.Roll(8);

	auto actualHistory = actual.History();
	auto actualScore = actual.Score();
	auto expectHistory = std::vector<Bowling::Frame>{ { {1, 4}, 5 }, {{4, 5}, 9}, {{6, 4}, 15}, {{5, 5}, 20}, {{10}, 11}, {{0, 1}, 1}, {{7, 3}, 16}, {{6, 4}, 20}, {{10}, 20}, {{10, 6, 8}, 24} };
	auto expectScore = 141;
	EXPECT_EQ(actualHistory, expectHistory);
	EXPECT_EQ(actualScore, expectScore);
}

TEST(TestGame, Roll_PerfectGame_ReturnScore300)
{
	auto actual = Bowling::Game{};

	for (int i = 0; i < 12; ++i)
		actual.Roll(10);
	
	auto actualHistory = actual.History();
	auto actualScore = actual.Score();
	auto expectHistory = std::vector<Bowling::Frame>{ {{ 10 }, 30 }, {{ 10 }, 30 }, {{ 10 }, 30 }, {{ 10 }, 30 }, {{ 10 }, 30 }, {{ 10 }, 30 }, {{ 10 }, 30 }, {{ 10 }, 30 }, {{ 10 }, 30 }, {{ 10, 10, 10 }, 30 } };
	auto expectScore = 300;
	EXPECT_EQ(actualHistory, expectHistory);
	EXPECT_EQ(actualScore, expectScore);
}