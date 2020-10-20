#include "gtest/gtest.h"
#include "ConflictSolver.h"

const ConflictSolver::Lines input{
	{"the solar system"},
	{"the number of planets are"},
	{"<<<<<<< HEAD"},
	{"nine"},
	{"minnus one"},
	{"======="},
	{"eight"},
	{">>>>>>> branch-a"},
	{"earth is the 3rd planet"}
};

const ConflictSolver::Lines inputWithTwoConflicts{
	{"the solar system"},
	{"the number of planets are"},
	{"<<<<<<< HEAD"},
	{"nine"},
	{"minnus one"},
	{"======="},
	{"eight"},
	{">>>>>>> branch-a"},
	{"earth is the 3rd planet"},
	{"<<<<<<< HEAD"},
	{"but pluto isn't"},
	{"======="},
	{"but pluto is"},
	{">>>>>>> branch-a"},
};

const ConflictSolver::Lines inputWithTwoConflictsInARow{
	{"the solar system"},
	{"the number of planets are"},
	{"<<<<<<< HEAD"},
	{"nine"},
	{"minnus one"},
	{"======="},
	{"eight"},
	{">>>>>>> branch-a"},
	{"<<<<<<< HEAD"},
	{"but pluto isn't"},
	{"======="},
	{"but pluto is"},
	{">>>>>>> branch-a"}
};

const ConflictSolver::Lines inputWithThreeConflictsInARow{
	{"the solar system"},
	{"the number of planets are"},
	{"<<<<<<< HEAD"},
	{"nine"},
	{"minnus one"},
	{"======="},
	{"eight"},
	{">>>>>>> branch-a"},
	{"<<<<<<< HEAD"},
	{"but pluto isn't"},
	{"======="},
	{"but pluto is"},
	{">>>>>>> branch-a"},
	{"<<<<<<< HEAD"},
	{"but pluto isn't"},
	{"======="},
	{"but pluto is"},
	{">>>>>>> branch-a"},
	{"das bittere ende"}
};

TEST(TestConflictSolver, SetConflict_AddConflictContents_SetInternalTable)
{
	ConflictSolver::ConflictSolver solver{};
	solver.SetConflict(input);

	auto actual = solver.GetConflict();
	ConflictSolver::Table expect{
		{
			"HEAD",
			{
				{
					"the solar system",
					"the number of planets are"
				},
				{
					"earth is the 3rd planet"
				}
			},
			{
				{
					"nine",
					"minnus one"
				}
			},
		},
		{
			"branch-a",
			{
				{
					"the solar system",
					"the number of planets are"
				},
				{
					"earth is the 3rd planet"
				}
			},
			{
				{
					"eight",
					""
				}
			},
		}
	};
	EXPECT_EQ(actual, expect);
}

TEST(TestConflictSolver, Solve_ConflictToLeft_UseOnlyLeft)
{
	ConflictSolver::ConflictSolver solver{};
	solver.SetConflict(input);

	auto actual = solver.Solve(ConflictSolver::SOLVE::LEFT, 0);
	ConflictSolver::Lines expect{
	{"the solar system"},
	{"the number of planets are"},
	{"nine"},
	{"minnus one"},
	{"earth is the 3rd planet"}
	};

	EXPECT_EQ(actual, expect);
}

TEST(TestConflictSolver, Solve_ConflictToRight_UseOnlyRight)
{
	ConflictSolver::ConflictSolver solver{};
	solver.SetConflict(input);

	auto actual = solver.Solve(ConflictSolver::SOLVE::RIGHT, 0);
	ConflictSolver::Lines expect{
	{"the solar system"},
	{"the number of planets are"},
	{"eight"},
	{"earth is the 3rd planet"}
	};

	EXPECT_EQ(actual, expect);
}

TEST(TestConflictSolver, Solve_ConflictToBoth_UseBothRightFirst)
{
	ConflictSolver::ConflictSolver solver{};
	solver.SetConflict(input);

	auto actual = solver.Solve(ConflictSolver::SOLVE::BOTH, 0);
	ConflictSolver::Lines expect{
	{"the solar system"},
	{"the number of planets are"},
	{"nine"},
	{"minnus one"},
	{"eight"},
	{"earth is the 3rd planet"}
	};

	EXPECT_EQ(actual, expect);
}

TEST(TestConflictSolver, Solve_TwoConflictsToLeft_UseOnlyLeft)
{
	ConflictSolver::ConflictSolver solver{};
	solver.SetConflict(inputWithTwoConflicts);

	auto actual = solver.Solve(ConflictSolver::SOLVE::LEFT, 0);
	actual = solver.Solve(ConflictSolver::SOLVE::LEFT, 1);
	ConflictSolver::Lines expect{
	{"the solar system"},
	{"the number of planets are"},
	{"nine"},
	{"minnus one"},
	{"earth is the 3rd planet"},
	{"but pluto isn't"}
	};

	EXPECT_EQ(actual, expect);
}

TEST(TestConflictSolver, Solve_TwoConflictsToRight_UseOnlyRight)
{
	ConflictSolver::ConflictSolver solver{};
	solver.SetConflict(inputWithTwoConflicts);

	auto actual = solver.Solve(ConflictSolver::SOLVE::RIGHT, 0);
	actual = solver.Solve(ConflictSolver::SOLVE::RIGHT, 1);
	ConflictSolver::Lines expect{
	{"the solar system"},
	{"the number of planets are"},
	{"eight"},
	{"earth is the 3rd planet"},
	{"but pluto is"}
	};

	EXPECT_EQ(actual, expect);
}

TEST(TestConflictSolver, Solve_TwoConflictsToBoth_UseBothRightFirst)
{
	ConflictSolver::ConflictSolver solver{};
	solver.SetConflict(inputWithTwoConflicts);

	auto actual = solver.Solve(ConflictSolver::SOLVE::BOTH, 0);
	actual = solver.Solve(ConflictSolver::SOLVE::BOTH, 1);
	ConflictSolver::Lines expect{
	{"the solar system"},
	{"the number of planets are"},
	{"nine"},
	{"minnus one"},
	{"eight"},
	{"earth is the 3rd planet"},
	{"but pluto isn't"},
	{"but pluto is"}
	};

	EXPECT_EQ(actual, expect);
}

TEST(TestConflictSolver, Solve_TwoConflictsToLeftAndRight_UseRightFirstLeftSecond)
{
	ConflictSolver::ConflictSolver solver{};
	solver.SetConflict(inputWithTwoConflicts);

	auto actual = solver.Solve(ConflictSolver::SOLVE::RIGHT, 0);
	actual = solver.Solve(ConflictSolver::SOLVE::LEFT, 1);

	ConflictSolver::Lines expect{
	{"the solar system"},
	{"the number of planets are"},
	{"eight"},
	{"earth is the 3rd planet"},
	{"but pluto isn't"}
	};
	EXPECT_EQ(actual, expect);
}

TEST(TestConflictSolver, Solve_TwoConflicts_KeepUnsolved)
{
	ConflictSolver::ConflictSolver solver{};
	solver.SetConflict(inputWithTwoConflicts);

	auto actual = solver.Solve(ConflictSolver::SOLVE::UNSOLVED, 0);
	ConflictSolver::Lines expect{
	{"the solar system"},
	{"the number of planets are"},
	{"<<<<<<< HEAD"},
	{"nine"},
	{"minnus one"},
	{"======="},
	{"eight"},
	{">>>>>>> branch-a"},
	{"earth is the 3rd planet"},
	{"<<<<<<< HEAD"},
	{"but pluto isn't"},
	{"======="},
	{"but pluto is"},
	{">>>>>>> branch-a"},
	};

	EXPECT_EQ(actual, expect);
}

TEST(TestConflictSolver, Solve_TwoConflictsInARow_UnsolvedAndSolvedToLeft)
{
	ConflictSolver::ConflictSolver solver{};
	solver.SetConflict(inputWithTwoConflictsInARow);

	auto actual = solver.Solve(ConflictSolver::SOLVE::UNSOLVED, 0);
	actual = solver.Solve(ConflictSolver::SOLVE::LEFT, 1);
	ConflictSolver::Lines expect{
	{"the solar system"},
	{"the number of planets are"},
	{"<<<<<<< HEAD"},
	{"nine"},
	{"minnus one"},
	{"======="},
	{"eight"},
	{">>>>>>> branch-a"},
	{"but pluto isn't"},
	};

	EXPECT_EQ(actual, expect);
}

TEST(TestConflictSolver, Solve_ThreeConflictsInARow_UnsolvedAndSolvedToLeft)
{
	ConflictSolver::ConflictSolver solver{};
	solver.SetConflict(inputWithThreeConflictsInARow);

	auto actual = solver.Solve(ConflictSolver::SOLVE::UNSOLVED, 0);
	actual = solver.Solve(ConflictSolver::SOLVE::LEFT, 1);
	ConflictSolver::Lines expect{
	{"the solar system"},
	{"the number of planets are"},
	{"<<<<<<< HEAD"},
	{"nine"},
	{"minnus one"},
	{"======="},
	{"eight"},
	{">>>>>>> branch-a"},
	{"but pluto isn't"},
	{"<<<<<<< HEAD"},
	{"but pluto isn't"},
	{"======="},
	{"but pluto is"},
	{">>>>>>> branch-a"},
	{"das bittere ende"}
	};

	EXPECT_EQ(actual, expect);
}