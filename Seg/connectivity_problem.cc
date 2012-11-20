#include <map>
#include <vector>
#include <string>
#include "utils.h"
#include "gtest/gtest.h" 

typedef std::vector<int> Vi;
typedef std::vector<int>::iterator ViIt;

using namespace std;
static const int N = 20;

void quick_find( Vi vpq ) {
	// ��������� - ��������� �������������
	int i, id[N];
	for ( i = 0; i < N; i++)
		id[i] = i;
		
	ViIt at = vpq.begin(), end = vpq.end();
	// ������ �����
	for ( ; at != end; ++(++at) ) {
		int p, q;
		
		// ������ ����
		ViIt copy_at;
		copy_at = at;
		p = *copy_at;
		q = *(++copy_at);
		
		// find
		if (id[p] == id[q]) {
			print(id, N);
			continue;	// ���� � ������(��?) - �� ������� � �� ���������
		}
			
		// union
		int t = id[p];
		for ( int i = 0; i < N; i++ )
			// ������ �������
			if (id[i] == t)
				id[i] = id[q];
		
		// ����������
		print(id, N);
		print(p, q);
	}
}

string quick_union( Vi vpq ) {
	string result;
	// ��������� - ��������� �������������
	int i, id[N];
	for ( i = 0; i < N; i++)
		id[i] = i;
		
	ViIt at = vpq.begin(), end = vpq.end();
	// ������ �����
	for ( ; at != end; ++(++at) ) {
		int p, q;
		
		// ������ ����
		ViIt copy_at;
		copy_at = at;
		p = *copy_at;
		q = *(++copy_at);
		print("\nPair", p, q);
		
		// find
		int i, j;
		for (i = p; i != id[i]; i = id[i]) {
			print( "i", i, "id[i]", id[i], "id[id[i]]", id[id[i]] );
		}
		//print("\n");
		for (j = q; j != id[j]; j = id[j]) {
			print( "j", j, "id[j]", id[j], "id[id[j]]", id[id[j]] );
		}
		if( i == j ) {
			print("Coupled\n");
			continue;
		}
		print("No coupled\n");
		result += int2string(p)+"-";
		result += int2string(q)+" ";
		id[i] = j;
		
		// ����������
		print(id, N);
	}
	return result;
}
TEST(ConnectivityTest, QuickUnionBase) {
	Vi vpq;
	vpq.push_back(3); vpq.push_back(4);
	vpq.push_back(4); vpq.push_back(9);
	vpq.push_back(8); vpq.push_back(0);
	vpq.push_back(2); vpq.push_back(3);
	vpq.push_back(5); vpq.push_back(6);
	vpq.push_back(2); vpq.push_back(9);
	vpq.push_back(5); vpq.push_back(9);
	vpq.push_back(7); vpq.push_back(3);
	vpq.push_back(4); vpq.push_back(8);
	vpq.push_back(5); vpq.push_back(6);
	vpq.push_back(0); vpq.push_back(2);
	vpq.push_back(6); vpq.push_back(1);
	
	// ���������
	//quick_find(vpq);
	string expect_result = "3-4 4-9 8-0 2-3 5-6 5-9 7-3 4-8 6-1 ";
	EXPECT_EQ( expect_result, quick_union(vpq) );
}

int main(int argc, char* argv[]) {
	testing::InitGoogleTest(&argc, argv);
	// ������������� �������� ����� ������ ������.
	testing::GTEST_FLAG(print_time) = true;
	return RUN_ALL_TESTS();
}

