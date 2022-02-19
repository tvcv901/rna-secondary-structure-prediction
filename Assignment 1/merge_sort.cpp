#include <iostream>
using namespace std ;
struct point
{
	int x, y ;
};
void merge(point p[], int l, int m, int r, bool c, bool o);
void sort(point p[], int l, int r, bool c, bool o);
int main()
{
	int n, i ;
	cout << "Enter number of points : " ;
	cin >> n ;
	cout << "\nEnter " << n << " points:\n" ;
	point p[n];
	for(i = 0; i < n; i++)
		cin >> p[i].x >> p[i].y ;
	sort(p, 0, n-1, false, true);
	cout << "\nThe " << n << " points in sorted order are : " ;
	for(i = 0; i < n; i++)
		cout << "(" << p[i].x << "," << p[i].y << ") " ;
}
void merge(point p[], int l, int m, int r, bool c, bool o)
{
	int n1 = m-l+1, n2 = r-m, i, j, k ;
	point p1[n1], p2[n2];
	for(i = 0; i < n1; i++)
		p1[i] = p[l+i];
	for(i = 0; i < n2; i++)
		p2[i] = p[m+1+i];
	i = 0 ;
	j = 0 ;
	k = l ;
	while((i < n1) && (j < n2))
	{
		if(c)
		{
			if(o)
			{
				if(p1[i].x < p2[j].x)
					p[k++] = p1[i++];
				else
					p[k++] = p2[j++];
			}
			else
			{
				if(p1[i].x > p2[j].x)
					p[k++] = p1[i++];
				else
					p[k++] = p2[j++];
			}	
		}
		else
		{
			if(o)
			{
				if(p1[i].y < p2[j].y)
					p[k++] = p1[i++];
				else
					p[k++] = p2[j++];
			}
			else
			{
				if(p1[i].y > p2[j].y)
					p[k++] = p1[i++];
				else
					p[k++] = p2[j++];
			}
		}
	}
	while(i < n1)
	{
		p[k++] = p1[i++];
	}
	while(j < n2)
	{
		p[k++] = p2[j++];
	}
}
void sort(point p[], int l, int r, bool c, bool o)
{
	// if(c) -> x else y
	// if(o) -> asc else desc
	if(l < r)
	{
		sort(p, l, (l+r)/2, c, o);
		sort(p, (l+r)/2 + 1, r, c, o);
		merge(p, l, (l+r)/2, r, c, o);
	}
}
