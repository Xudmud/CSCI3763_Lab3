#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include <fcntl.h>
#include <stdbool.h>

int findKey(int key[], bool inMst[], int nodeCount);

int main(int argc, char const *argv[])
{
    /* First check the correct number of arguments are passed */
    if(argc != 2)
    {
        fprintf(stderr,"Usage: wic6774mst <input file>\n");
        exit(1);
    }
    /* Declare objects to hold time values */
    struct timeval beg, end;
    float tot;

    /* Start: get the current time */
    gettimeofday(&beg, 0);
    /* Declare variables */
    int nodeCount;
    int lef, rig, cos;
    int totCost = 0;

    /* Open the input file */
    FILE* infile = fopen(argv[1],"r");
    if(infile == NULL)
    {
        fprintf(stderr,"Failed to open input file.\n");
        exit(2);
    }

    /* First line has the number of nodes */
    fscanf(infile,"%d",&nodeCount);

    /* Use Prim's Algorithm. */
    /* For each node, find the cheapest node to connect to while avoiding a cycle. */
    /* First declare a two-dimensional array of ints. arr[x][y] represents the cost */
    /* for an edge x-y.  A value of 0 is used for arr[x][y] where x=y, to indicate */
    /* the nodes. An arbitrarily large value (2^30) is used to indicate no edge */
    /* between two nodes. */
    /* Initialize a graph to hold costs to each node. */
    int primGraph[nodeCount][nodeCount];
    /* Declare a MST. Should be [nodeCount-1] x 3 */
    int mstGraph[nodeCount-1][3];
    /* Declare an array of booleans, to keep track of nodes already in the tree */
    bool in_mst[nodeCount];

    /* initialize each  boolean to false */
    for(unsigned int i = 0; i < nodeCount; ++i)
    {
        in_mst[i] = false;
    }
    /* Build a graph to use. */
    /* Read in the file and assign the edge value to the two-dimensional array */
    for(int i = 0; i < nodeCount; ++i)
    {
        for(int j = 0; j < nodeCount; ++j)
        {
            fscanf(infile,"%d%d%d",&lef,&rig,&cos);
            /* A cost of 2^30 means there is no connection */
            if(cos != 1073741824)
                primGraph[lef-1][rig-1] = cos;
            else
                /* So set it to 0, indicating no edge *
                 * This avoids a possibility that 2^30 is inadvertantly used
                 * as the cost of a nonexistent edge */
                primGraph[lef-1][rig-1] = 0;
        }
    }
    /* Set the first node to be root */
    in_mst[0] = 1;
    /* Graph is built. Now figure out the edges */
    /* Number of edges should be one less than the number of nodes. */
    /* Go in order, connecting the cheapest edge not currently in the tree */
    /* to the tree. */
    for(unsigned int i = 0; i < nodeCount-1; ++i)
    {
        int cheapNode = -1;
        int cheapCost = 999999999;
        int cheapPar = -1;
        /* Traverse through the tree, for each node in the tree grab the cheapest */
        /* edge not in the tree. */
        for(unsigned int y = 0; y < nodeCount; ++y)
        {
            //fprintf(stderr,"Position %d: ",y);
            /* Only check if the node is in the tree */
            if(in_mst[y])
            {
                //fprintf(stderr,"Checking...\n");
                for(unsigned int x = 0; x < nodeCount; ++x)
                {
                    //fprintf(stderr,"Checking node: %d|Cost: %d\n",x,primGraph[y][x]);
                    if(primGraph[y][x] && !(in_mst[x]) && primGraph[y][x] < cheapCost)
                    {
                        cheapNode = x;
                        cheapPar = y;
                        cheapCost = primGraph[y][x];
                    }
                }
            }
        }
        /* At this point, we should have the cheapest node, and the cheapest
         * parent. Add this to the graph. */
        //fprintf(stderr,"Position: %d|Parent node: %d|Chosen node: %d|Cost: %d\n",i,cheapPar,cheapNode,cheapCost);
        mstGraph[i][0] = cheapPar;
        mstGraph[i][1] = cheapNode;
        mstGraph[i][2] = cheapCost;
        in_mst[cheapNode] = true;
    }
    /* Print the MST */
    fprintf(stdout,"Final MST\n");
    for(int i = 0; i < nodeCount-1; ++i)
    {
        fprintf(stdout,"%d -> %d : %d\n",mstGraph[i][0]+1,mstGraph[i][1]+1,mstGraph[i][2]);
        /* And increment the cost */
        totCost += mstGraph[i][2];
    }
    fprintf(stdout,"Minimum Cost: ");
    /* Start minimum cost at an arbitrarily high number */
    int min = 999999999;
    for(int i = 1; i < nodeCount-1; ++i)
    {
        if(mstGraph[i][2] < min)
            min = mstGraph[i][2];
    }
    fprintf(stdout,"%d\n",min);
    fprintf(stdout,"Total cost: %d\n------\n",totCost);
    /* Finished: get the current time again */
    gettimeofday(&end,0);
    /* Calculate total time elapsed. */
    /* (end seconds - beginning seconds) + ((end microseconds - beginning microseconds) / 1000) */
    tot = (end.tv_sec - beg.tv_sec) + ((end.tv_usec - beg.tv_usec) / 1000.0f);
    fprintf(stdout,"Total time taken: %.2f ms\n",tot);
    return(0);
}

/*int findKey(int key[], bool inMst[], int nodeCount)
{
    /* Initialize minimum value */
/*    int min = 999999999;
    int min_index;
    /* Find the cheapest path to a node not yet in the tree */
/*    for(int i = 0; i < nodeCount; ++i)
    {
        if(!(inMst[i]) && key[i] < min)
        {
            min = key[i];
            min_index = i;
        }
    }
    return min_index;
}
*/
