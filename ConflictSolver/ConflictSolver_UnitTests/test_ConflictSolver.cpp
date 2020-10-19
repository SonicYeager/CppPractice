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
					0,
					"the solar system"
				},
				{
					0,
					"the number of planets are"
				},
				{
					1,
					"earth is the 3rd planet"
				}
			},
			{
				{
					0,
					"nine"
				},
				{
					0,
					"minnus one"
				}
			},
			2
		},
		{
			"branch-a",
			{
				{
					0,
					"the solar system"
				},
				{
					0,
					"the number of planets are"
				},
				{
					1,
					"earth is the 3rd planet"
				}
			},
			{
				{
					0,
					"eight"
				},
			},
			2
		}
	};
	EXPECT_EQ(actual, expect);
}