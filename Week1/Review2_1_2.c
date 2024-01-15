#include <stdio.h>
#include <stdlib.h>

typedef struct score {
	int midterm;
	int final;
} Score;

void printScore(Score* p)
{
	printf("중간고사 성적은 %d\n", p->midterm);
	printf("기말고사 성적은 %d\n", p->final);
}

Score* biggerScore(Score* p1, Score* p2)
{
	Score* p;
	p = (Score*)malloc(sizeof(Score));

	if (p1->midterm > p2->midterm)
		p->midterm = p1->midterm;
	else
		p->midterm = p2->midterm;

	if (p1->final > p2->final)
		p->final = p1->final;
	else
		p->final = p2->final;

	return p;
}

Score* totalScore(Score* p1, Score* p2)
{
	Score* p;
	p = (Score*)malloc(sizeof(Score));

	p->midterm = p1->midterm + p2->midterm;
	p->final = p1->final + p2->final;

	return p;
}

Score* createScore(int m, int f)
{
	Score* p = (Score*)malloc(sizeof(Score));

	p->midterm = m;
	p->final = f;

	return p;
}

int main(void)
{
	Score p1, p2;
	Score* p3;

	p3 = (Score*)malloc(sizeof(Score));

	p1.midterm = 50;
	p1.final = 100;

	p2.midterm = 70;
	p2.final = 70;

	printScore(&p1);
	printScore(&p2);

	printf("----------------------------\n");
	printf("둘 중 성적이 좋은 점수:\n");
	printScore(biggerScore(&p1, &p2));

	printf("----------------------------\n");
	printf("두 성적의 총합:\n");
	printScore(totalScore(&p1, &p2));

	printf("----------------------------\n");
	p3 = createScore(100, 100);
	printScore(p3);
}