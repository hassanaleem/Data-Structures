#ifndef GRAPH__CPP
#define GRAPH__CPP
#include "Graph.h"

//
// Add your constructor code here. It takes the filename and loads
// the graph from the file, storing into your representation of the
// graph. MAKE SURE you use the addEdge function here, and pass the 
// flag to it too.
//
Graph::Graph(string filename, bool flag)
{
	
	ifstream file;
	file.open(filename);
	 
	string graphSize;
	string temp ="";
	string graphData;
	string a;

	getline(file, graphSize);
	
	int i=2;
	while(graphSize[i]!= '\0')
	{
		temp += graphSize[i];
		i++;
	}
	size = stoi(temp);

	graph.resize(size);
	for(int i=0; i<size; i++)
	{
		graph[i].resize(size);
	}

	for(int i = 0; i < size; i++)
	{
		for(int j = 0; j < size; j++)
		{
			graph[i][j] = NULL;
		}
	}
	
	getline(file, a); //no use of this line so stored in dummy variable

	while(!file.eof()) //read all data until the end of file. the first char is the start, second is dest followed by weight
	{
		getline(file, graphData);
		if(graphData.length())
		{
			char s, e;
			int w;
			
			s = graphData[0];
			e = graphData[2];

			int i=4;
			temp = "";

			while(graphData[i] != '\0')
			{
				temp += graphData[i];
				i++;
			}
			w = stoi(temp);
			
			addEdge(s, e, w, flag);
		}		
	}
}

//
// Adds an edge to the graph. Useful when loading the graph from file.
// The flag determines whether the edges will be added according to a
// directed or undirected graph.
//
void Graph::addEdge(char start, char end, int weight, bool flag)
{
	shared_ptr <Edge> newEdge (new Edge);
	newEdge->origin = start;
	newEdge->dest = end;
	newEdge->weight = weight;
	int s  = int(start) - 65;
	int e = int(end) - 65;

	graph[s][e] = newEdge;
	if(!flag) // if graoh is undirected, we add both edges. the second edge just has start and end swapped
	{
		shared_ptr <Edge> newEdge2 (new Edge);
		newEdge2->origin = end;
		newEdge2->dest = start;
		newEdge2->weight = weight;

		graph[e][s] = newEdge2;

	} 

	return;
}

//
// Returns the display of the graph as a string. Make sure
// you follow the same output as given in the manual.
//
string Graph::display()
{
	// TODO
	bool check;
	string result = "";
	for(int i=0; i<size; i++)
	{
		check = false;
		for(int j=0; j<size; j++)
		{
			if(graph[i][j]) // if an edge exists, add its details in string according to proper formatting
			{
				result += "(" ;
				result += graph[i][j]->origin;
				result += ",";
				result += graph[i][j]->dest;
				result += ",";
				
				result += to_string(graph[i][j]->weight);
				result += ")";


				if(j != size-1)// taking care of spaces at the end of line
				{
					result += " ";
				}

				
				check = true;

			}
		}
		if(check)
		{
			result += '\n'; 
		}
	}

	return result;
}

// Returns whether the destination city is reachable from the
// origin city or not.
//
bool Graph::Reachable(char start, char end)
{
	// TODO
	queue <char> que;
	vector <bool> visited;
	char temp;

	visited.resize(size);
	for(int i=0; i<size; i++)
	{
		visited[i] = false;
	}

	visited[int(start)-65] = true;

	que.push(start);
	while(!que.empty())
	{
		temp = que.front();
		que.pop();

		if(temp == end)
		{
			return true;
		}

		for(int i=0; i<size; i++)
		{
			if(graph[int(temp)-65][i] && !visited[i] )
			{
				visited[i] = true;
				que.push(char(i+65));
			}
		}
	}

	return false;
}

//
// Returns the weight of shortest path between origin and destination cities.
// Return -1 if no path exists.
//
int Graph::Dijkstra(char start, char dest)
{
	int inf = 100;
	// TODO
	
	queue <char> que;
	vector <int> weight;
	char temp;
	
	weight.resize(size);
	for(int i=0; i<size; i++)
	{
		weight[i] = inf;
	}

	weight[int(start)-65] = 0;

	que.push(start);

	while(!que.empty())
	{
		temp = que.front();
		que.pop();

		for(int i=0; i<size; i++)
		{
			if(graph[int(temp)-65][i])
			{
				if(weight[int(temp)-65] + graph[int(temp)-65][i]->weight < weight[i])
				{
					weight[i] = weight[int(temp)-65] + graph[int(temp)-65][i]->weight;
					que.push(graph[int(temp)-65][i]->dest);
				}
			}
		}
	}

	if(weight[int(dest)-65] == inf)
	{
		return -1;
	}

	return weight[int(dest)-65];

}

//
// Implement topological sort on the graph and return the string of the sorted cities
//
string Graph::topoSort()
{
	//TODO
	vector<int> indegree;
	queue<int> inDegreeQueue;
	string output = "";
	indegree.resize(size);
	for (int i=0; i<size; i++)
	{
		indegree[i]=0;
	}
	


	int inDeg;
	for(int i=0; i<size; i++)
	{
		inDeg = 0;
		for(int j=0; j<size; j++)
		{	
			if(graph[j][i])
			{
				inDeg++;
			}
		}
		indegree[i] = inDeg;
	} 

	int vecInDegSize = indegree.size();

	int i=0;
	while(true)
	{
		if(i==size)
		{
			break;
		}
		else if(!indegree[i])
		{
			inDegreeQueue.push(i);
			indegree[i] = -1;
		}
		i++;

	}

	int temp;
	while (!inDegreeQueue.empty())
	{
		temp = inDegreeQueue.front();
		inDegreeQueue.pop();
		
		i=0;

		while(true)
		{
			if(i==size)
			{
				break;
			}
			else if(graph[temp][i])
			{
				indegree[i] -= 1;
				
			}
			i++;
		}

		i=0;
		while(true)
		{
			if(i==vecInDegSize)
			{
				break;
			}
			else if(!indegree[i])
			{
				inDegreeQueue.push(i);
				indegree[i] = -1;
				
			}
			i++;
		}
		output +=  char(temp+65);
	}
	return output;
}

#endif
