
int main() {
    return 0;
}


void __global__ extension(uint32_t* query, Node node, Node* reachableNodes){
  int l = LCP(query[], node.content[])
  node.col = l+node.col;
}