void SetDepth_Parent(Tree root, int Depth, Tree Parent, int x, int y, Tree *xParent, Tree *yParent, int *xDepth, int *yDepth){ // x,y为两个结点的值
    if(!root) return;
    if(root->val==x){
        *xParent = Parent;
        *xDepth = Depth;
    }
    else if(root->val==y){
        *yParent = Parent;
        *yDepth = Depth;
    }
    if(*xDepth && *yDepth) return;
    if(root->left) SetDepth_Parent(root->left,Depth+1,root,x,y,xParent,yParent,xDepth,yDepth);
    if(*xDepth && *yDepth) return;
    if(root->right) SetDepth_Parent(root->right,Depth+1,root,x,y,xParent,yParent,xDepth,yDepth);
}
//调用时，SetDepth_Parent(root,0,NULL,x,y,&xParent,&yParent,&xDepth,&yDepth); root为根节点
