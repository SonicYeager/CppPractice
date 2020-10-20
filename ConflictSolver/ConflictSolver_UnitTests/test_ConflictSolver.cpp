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

TEST(TestConflictSolver, Solve_ConflictToLeft_Solved)
{
	ConflictSolver::ConflictSolver solver{};
	solver.SetConflict(input);

	auto actual = solver.Solve(ConflictSolver::SOLVE::LEFT);
	ConflictSolver::Lines expect{
	{"the solar system"},
	{"the number of planets are"},
	{"nine"},
	{"minnus one"},
	{"earth is the 3rd planet"}
	};

	EXPECT_EQ(actual, expect);
}

TEST(TestConflictSolver, Solve_ConflictToRight_Solved)
{
	ConflictSolver::ConflictSolver solver{};
	solver.SetConflict(input);

	auto actual = solver.Solve(ConflictSolver::SOLVE::RIGHT);
	ConflictSolver::Lines expect{
	{"the solar system"},
	{"the number of planets are"},
	{"eight"},
	{"earth is the 3rd planet"}
	};

	EXPECT_EQ(actual, expect);
}

TEST(TestConflictSolver, Solve_ConflictToBoth_Solved)
{
	ConflictSolver::ConflictSolver solver{};
	solver.SetConflict(input);

	auto actual = solver.Solve(ConflictSolver::SOLVE::BOTH);
	ConflictSolver::Lines expect{
	{"the solar system"},
	{"the number of planets are"},
	{"eight"},
	{"nine"},
	{"minnus one"},
	{"earth is the 3rd planet"}
	};

	EXPECT_EQ(actual, expect);
}