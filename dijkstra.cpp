// John Cruz 
// 11/7/2021
// Project 3

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cmath>

using namespace std;
template <typename T>
void readVector(vector<T> vec) {
	for (int i = 0; i < vec.size(); i++) {
		cout << vec[i];
		cout << "\n";
	}
}

template <typename T>
void read2DVector(vector<vector<T>> vec) {
	for (int i = 0; i < vec.size(); i++) {
		for (int j = 0; j < vec[i].size(); j++) {
			cout << vec[i][j];
			cout << " ";
		}
		cout << "\n";
	}
}

template <typename T>
void readPaths(vector<vector<T>> vec) {
	for (int i = 0; i < vec.size(); i++) {
		for (int j = 0; j < vec[i].size(); j++) {
			cout << vec[i][j];		
			cout << " - ";
	
		}
		cout << "\n";
	}
}


vector <string> filelines_to_vector(string file_name) {
	string line;
	vector <string> file_content;
	fstream my_file;

	//my_file.open("File_1.txt", ios::in);
	my_file.open(file_name, ios::in);

	while (getline(my_file, line)) {
		file_content.push_back(line);
		//cout << line << "\n";
	}
	//file_content.push_back("#"); // sequnce delimiters
	my_file.close();
	return file_content;
}


vector<string> retfile(string path) {

	vector<string> lines;
	fstream myfile;
	myfile.open(path, ios::in);

	char ch;
	string temp_line;
	while (true) {
		myfile >> ch;
		if (myfile.eof()) {
			break;
		}

		if (ch == '*') {
			lines.push_back(temp_line);
			temp_line.clear();
		}

		else {
			temp_line.push_back(ch);
		}
		//cout << ch;
	}
	myfile.close();
	return lines;
}


vector<vector<string>> file_to_2x_vector(string path) {
	vector<string> datalines = filelines_to_vector(path);
	vector<vector<string>> ret_data;
	vector<string> node;
	string line, chs;
	char temp;
	string st;

	vector<string> next_hop;


	for (int line_num = 1; line_num < datalines.size(); line_num++) {
		line = datalines[line_num];
		for (int i = 0; i < line.size(); i++){
			if (line[i] != ' ' ) {
				st.push_back(line[i]);
			}
			else {
				node.push_back(st);
				st.clear();
			}
		}
		node.push_back(st);
		st.clear();
		ret_data.push_back(node);
		node.clear();

		/*	node.push_back(line.substr(0,1));
			node.push_back(line.substr(2, 1));
			node.push_back(line.substr(4, 3));
			ret_data.push_back(node);
			node.clear();*/
	}
	return ret_data;
}


vector<string> nodes_in_graph(vector<vector<string>> graph_data) {
	//vector<vector<string>> graph = file_to_2x_vector("Nodes.txt");
	vector<vector<string>> graph = graph_data;
	vector<string> node;

	bool is_in = false;

	node.push_back(graph[0][0]);

	for (int i = 0; i < graph.size(); i++) {
		for (int j = 0; j < node.size(); j++) {
			if (graph[i][0] == node[j]) { 
				is_in = true; break; 
			}
		}
		if (!is_in) {
			node.push_back(graph[i][0]);
		}
		is_in = false;
	}

	for (int i = 0; i < graph.size(); i++) {
		for (int j = 0; j < node.size(); j++) {
			if (graph[i][1] == node[j]) { is_in = true; break; }
		}
		if (!is_in) {
			node.push_back(graph[i][1]);
		}
		is_in = false;
	}
	//readVector(node);
	return node;
}


vector<vector<string>> connecting_edges(vector<vector<string>> graph, string node) {
	int number_of_nodes = nodes_in_graph(graph).size();
	vector <vector<string>> edges;

	for (int i = 0; i < graph.size(); i++) {
		if (graph[i][0] == node) {
			edges.push_back(graph[i]);
		}
	}
	for (int i = 0; i < graph.size(); i++) {
		if (graph[i][1] == node) {
			edges.push_back(graph[i]);
		}
	}
	return edges;
}


vector<string> connecting_nodes(vector<vector<string>> avalible_edges) {
	//vector<vector<string>> graph = file_to_2x_vector("Nodes.txt");
	vector<vector<string>> graph = avalible_edges;
	vector<string> node;

	bool is_in = false;

	if (node.empty()) {
		node.push_back(graph[0][0]);
	}

	for (int i = 0; i < graph.size(); i++) {
		for (int j = 0; j < node.size(); j++) {
			if (graph[i][0] == node[j]) {
				is_in = true; break;
			}
		}
		if (!is_in) {
			node.push_back(graph[i][0]);
		}
		is_in = false;
	}

	for (int i = 0; i < graph.size(); i++) {
		for (int j = 0; j < node.size(); j++) {
			if (graph[i][1] == node[j]) {
				is_in = true; break;
			}
		}
		if (is_in) {
			node.push_back(graph[i][1]);
		}
		is_in = false;
	}
	return node;
}



bool is_in_visited( vector<string> vis, string look_for) {
	//bool flag = false;
	
	for (int i = 0; i < vis.size(); i++) {
		if (vis[i] == look_for) {
			return true;
		}
	}
	return false;
}



bool is_in(vector<string> a, string b) {
	//bool flag = false;

	for (int i = 0; i < a.size(); i++) {
		if (a[i] == b) {
			return true;
		}
	}
	return false;
}

bool is_adj(vector<vector<string>> data, string a,  string b) {
	//bool flag = false;

	for (int i = 0; i < data.size(); i++) {
		if ((data[i][0] == a && data[i][1] == b) || (data[i][0] == b && data[i][1] == a)) {
			return true;
		}
	}
	return false;
}



vector<string> get_adj_nodes(vector<vector<string>> data, string src, vector<string> visited, bool a = true) {
	vector<vector<string>> edges = connecting_edges(data, src);
	vector<string> adj_nodes = nodes_in_graph(connecting_edges(data, src));

	//adjacent nodes to the src node
	for (int i = 0; i < adj_nodes.size(); i++) {
		if (adj_nodes[i] == src) {
			adj_nodes.erase(adj_nodes.begin() + i);
		}
	}


	if (a) {

		if (!visited.empty()) {
			for (int j = 0; j < visited.size(); j++) {
				for (int i = 0; i < adj_nodes.size(); i++) {
					if (adj_nodes[i] == visited[j]) {
						adj_nodes.erase(adj_nodes.begin() + i);
					}
				}
			}

		}

	}
	return adj_nodes;
}

vector<vector<string>> get_adj_node_w_weight(vector<vector<string>> data, string src, vector<string> visited, bool a = true) {

	vector<vector<string>> edges = connecting_edges(data, src);
	vector<string> adj_node = get_adj_nodes(data, src, visited, a);
	vector<vector<string>> dict;

	for (int i = 0; i < adj_node.size(); i++) {
		for (int j = 0; j < edges.size(); j++) {
			if (adj_node[i] == edges[j][0]) {
				vector<string> temp;
				temp.push_back(adj_node[i]);
				temp.push_back(edges[j][2]);
				dict.push_back(temp);
				temp.clear();
			}

		}
	}
	for (int i = 0; i < adj_node.size(); i++) {
		for (int j = 0; j < edges.size(); j++) {
			if (adj_node[i] == edges[j][1]) {
				vector<string> temp;
				temp.push_back(adj_node[i]);
				temp.push_back(edges[j][2]);
				dict.push_back(temp);
				temp.clear();
			}

		}
	}



	return dict;

}


int get_position(vector<string> nodes_in_graph, string src) {
	int pos;
	for (int i = 0; i < nodes_in_graph.size(); i++) {
		if (nodes_in_graph[i] == src) {
			pos = i;
		}
	}
	return pos;

}


float min_path_cost(vector<vector<string>> dict) {

	// set new min
	float min = 1111111.0;
	for (int i = 0; i < dict.size(); i++) {
		if (stof(dict[i][1]) < min) {
			min = stof(dict[i][1]);
			
		}
	}
	return min;
}


string min_path_vertext(vector<vector<string>> dict) {
	string vertext_s;
	// set new min
	float min = 1111111.0;
	for (int i = 0; i < dict.size(); i++) {
		if (stof(dict[i][1]) < min) {
			vertext_s = dict[i][0];
		}
	}
		return vertext_s;
}


vector<string> get_all_short_paths(string src, vector<string> nodes, vector<string> previous) {
	vector<string> path;
	path.push_back(src);
	for (int i = 0; i < nodes.size(); i++)
	{
		if (nodes[i] == src && (previous[i]) != "-") {
			src = previous[i];
			path.push_back(src);
			i = 0;
		}
	}
	return path;
}



vector<string> get_next_hop (string src, vector<vector<string>> paths) {
	vector<string> next_hop;
	
	for (int i = 0; i < paths.size(); i++) {
		for (int j = 0; j < paths[i].size(); j++) {
			if (src == paths[i][j] && paths[i].size() > 1)	{
				next_hop.push_back("(" + paths[i][j] + "," + paths[i][j - 1] + ")");
			}
			else if (src == paths[i][j] && paths[i].size() == 1) {
				next_hop.push_back("-");	
			}
		}
	}
	return next_hop;
}


vector<vector<string>>  dijkstra_algorithm(vector<vector<string>> data, string src, bool show_paths = false) {
	vector<string> nodes = nodes_in_graph(data);
	vector<float> min_dist;
	vector<string> prevs;
	vector<string> temp;
	vector<vector<string>> dict;
	vector<vector<string>> paths ;
	vector<string> unvisited;


	vector<string> visited;
	temp.push_back(src);
	vector<vector<string>> routing_table;
	vector<string> next_hop;
	string og = src;

	// populate distance array to be max number exepter for the src node.
	for (int i = 0; i < nodes.size(); i++) {
		if (nodes[i] == src) {
			min_dist.push_back(0.0);
			temp.push_back(nodes[i]);
			dict.push_back(temp);
			temp.clear();
		}
		else {
			min_dist.push_back(9999.99);
		}
	}

	// populate array with '-' to show that the previous node has not been found
	for (int i = 0; i < nodes.size(); i++) {
		prevs.push_back("-");
	}

	// populate array of unvisited nodes
	for (int i = 0; i < nodes.size(); i++) {
		if (src != nodes[i]) {
			unvisited.push_back(nodes[i]);
		}
	}

	while (!dict.empty())
	{
		vector<string> adj_nodes = get_adj_nodes(data, src, visited, true);
		dict = get_adj_node_w_weight(data, src, visited, true);
		int src_pos = get_position(nodes, src);

		for (int i = 0; i < nodes.size(); i++) {
			for (int j = 0; j < dict.size(); j++) {
				if (nodes[i] == dict[j][0] && (!is_in_visited(visited, dict[j][0]))) {
					float temp_f = stof(dict[j][1]) + min_dist[src_pos];
					if (temp_f < min_dist[i]) {
						min_dist[i] = temp_f;
						//min_dist[i] = stof(dict[j][1]) + min_dist[src_pos];

						// set previous nodes
						if (nodes[i] != og ) {
							prevs[i] = src;
						 }
					}
				}
			}
		}
		
		// set new min
		float min = min_path_cost(dict);
		//string min_vertext = min_path_vertext(dict);

		// set new src to min cost path and put src in the visited array
		for (int i = 0; i < dict.size(); i++) {
			if (stof(dict[i][1]) == min ) {
				visited.push_back(src);		
				src = dict[i][0];
				//break;  // break sometimes fixed some bug in distancing and breaks other. Needs extra logic possibly.
			}
		}
	}

	//convert min_dist to string
	vector<string> min_dist_string;
	for (int i = 0; i < min_dist.size(); i++){
		min_dist_string.push_back( to_string(min_dist[i]) );
	}

	for (int i = 0; i < nodes.size(); i++) {
			paths.push_back(get_all_short_paths(nodes[i], nodes, prevs));
		}
	
	if (show_paths) {
		return paths;
	}

		 
	next_hop = get_next_hop(og, paths);

	//readVector(next_hop);

	// paths.clear();
	// nodes , mindist ,  next_hop, path
	routing_table.push_back(nodes);
	routing_table.push_back(next_hop);

	for (int i = 0; i < min_dist.size(); i++) {
		temp.push_back(to_string(min_dist[i]));
	}
	routing_table.push_back(temp);
	temp.clear();


	return routing_table;
}


int main()
{
	vector<vector<string>> graph = file_to_2x_vector("Nodes.txt");
	vector<string> total_nodes = nodes_in_graph(graph);


	for (size_t i = 0; i < total_nodes.size(); i++) {
		vector<vector<string>> shortest_path = dijkstra_algorithm(graph, total_nodes[i]);


		cout << "============== Node "<< total_nodes[i] <<  " ===================" << endl;
		cout << "NODES" << "\t\t" << "N_NOP" << "\t\t" << "DISTANCE" << endl;
		for (int i = 0; i < shortest_path[0].size(); i++) {
			//cout << "======= " << total_nodes[i] << " ========" << endl;
			cout << shortest_path[0][i] << "\t\t" << shortest_path[1][i] << "\t\t" << shortest_path[2][i] << endl;

		}
		cout << "\n";
	}

	cout << "====================================" << endl;
	cout << "=========       Paths       ========" << endl;
	cout << "====================================" << endl;

	for (int i = 0; i < total_nodes.size();i++) {
		cout << "============== Node " << total_nodes[i] << " ===================" << endl;

		readPaths(dijkstra_algorithm(graph, total_nodes[i], true));
		cout << "\n";
	}







	//cout << shortest_path[1][6] << endl;


	return 0;
}

