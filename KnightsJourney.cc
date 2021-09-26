#include <iostream>
using namespace std;

bool checkForFreshPosition(int pos, int travelcount, int travelled[]);
int getValidNeighbours(int x, int y, int arr[]);
int getLowestPossibilityNeighbourForCurrentPos(int travelcount, int travelled[], int neighs[]);
bool isPosValid(int x, int y, int N);
int travel(int travelcount, int travelled[]);
void printTravel(int travelcount, int travelled[]);
void printNeighbours(int x, int y, int neighcount, int neighs[]);

int BOARDWIDTH = 8;
int MAX_MOVES = 8;
bool isPosValid(int x, int y, int N)
{
    if(x >= 0 && x <= N-1 && y >= 0 && y <= N-1)
        return true;
    return false;
}

int getValidNeighbours(int x, int y, int arr[])
{
    
    int a[] = {1,2};
    int count = 0;
    //std::cout<<"size of a is "<<sizeof(a)/sizeof(int)<<endl;
    for(int i = 0; i < 2; i++)
    {
        for(int j = 0; j < 2; j++)
            {   
                if(a[i]==a[j])
                    continue;
                //std::cout<<"a[i] = "<<a[i]<<" a[j] ="<<a[j]<<endl;
                if(isPosValid(x+a[i], y+a[j], BOARDWIDTH))
                {
                    arr[count] = (x+a[i]) + (BOARDWIDTH)*(y+a[j]);
                    //std::cout<<"x = "<<x+a[i]<<" y = "<<y+a[j]<<endl;
                    count++;
                }

                if(isPosValid(x-a[i], y+a[j], BOARDWIDTH))
                {
                    arr[count] = (x-a[i]) + (BOARDWIDTH)*(y+a[j]);
                    //std::cout<<"x = "<<x-a[i]<<" y = "<<y+a[j]<<endl;
                    count++;
                }

                if(isPosValid(x+a[i], y-a[j], BOARDWIDTH))
                {
                    arr[count] = (x+a[i]) + (BOARDWIDTH)*(y-a[j]);
                    //std::cout<<"x = "<<x+a[i]<<" y = "<<y-a[j]<<endl;
                    count++;
                }

                if(isPosValid(x-a[i], y-a[j], BOARDWIDTH))
                {
                    arr[count] = (x-a[i]) + (BOARDWIDTH)*(y-a[j]);
                    //std::cout<<"x = "<<x-a[i]<<" y = "<<y-a[j]<<endl;
                    count++;
                }

            }
            
    }
    return count;

}

int main()
{
    int x,y;
    std::cout<<"x ?"<<endl;
    cin>>x;
    std::cout<<endl<<"y ?"<<endl;
    cin>>y;
    std::cout<<endl<<" x = "<<x<<" y = "<<y<<endl;
    int arr[MAX_MOVES];
    int num = getValidNeighbours(x,y, arr);
    printNeighbours(x, y, num, arr);
    /*for(int i = 0; i < num; i++)
    {
        //std::cout<<arr[i]<<endl;
        int y1 = arr[i]/(BOARDWIDTH);
        int x1 = arr[i] - y1*(BOARDWIDTH);
        
        std::cout<<"x = "<<x1<<" y = "<<y1<<endl;
    }*/
    /*
    int travelled[BOARDWIDTH*BOARDWIDTH];
    int travelcount = 1;
    travelled[0] = x + (BOARDWIDTH)*y;
    //std::cout<<"getting lowest possible position"<<endl;
    
    //int sortedneighs[BOARDWIDTH];
    //int nums = getLowestPossibilityNeighbourForCurrentPos(travelcount, travelled, sortedneighs);
    //std::cout<<"lowest neighbours are "<<nums<<endl;
    //for(int i = 0; i < nums; i++)
    //{
    //    std::cout<<"neighbor = "<<sortedneighs[i]<<endl;
    //}
    
    travelcount = travel(travelcount, travelled);
    //std::cout<<"travelcount = "<<travelcount<<endl; 
    printTravel(travelcount, travelled);
    */
    int travelled[BOARDWIDTH*BOARDWIDTH];
    int travelcount = 1;
    travelled[0] = x + (BOARDWIDTH)*y;
    travelcount = travel(travelcount, travelled);
    //printTravel(travelcount, travelled);

}

void printNeighbours(int x, int y, int neighcount, int neighs[])
{
    int pos = y*BOARDWIDTH + x;
    std::cout<<endl<<"___________________________________________"<<endl;
    for(int j = BOARDWIDTH-1; j >= 0; j--)
    {
        for(int k = 0; k < BOARDWIDTH; k++)
        {
            std::cout<<"|";
            bool found = false;
            for(int l = 0; l < neighcount; l++)
            {
                
                if(neighs[l] == k + BOARDWIDTH*j)
                {
                    std::cout<<neighs[l]<<"  ";
                    found = true;
                }
                
                
            }
            if(pos == k + BOARDWIDTH*j)
            {
                found = true;
                std::cout<<" * ";
            }
            if(!found)
                std::cout<<"    ";
        }
    std::cout<<endl<<"___________________________________________"<<endl;
    }   
}

void printTravel(int travelcount, int travelled[])
{
    std::cout<<endl<<"____________________________________________"<<endl;
    for(int j = BOARDWIDTH-1; j >= 0; j--)
    {
        for(int k = 0; k < BOARDWIDTH; k++)
        {
            for(int l = 0; l < travelcount; l++)
            {
                if(travelled[l] == k + BOARDWIDTH*j)
                {
                    std::cout<<" | "<<l+1;
                }
            }
        }
    std::cout<<endl<<"____________________________________________"<<endl;
    }   
}

int travel(int travelcount, int travelled[])
{
    //std::cout<<"travelcount is "<<travelcount<<endl;
    int neighs[BOARDWIDTH];
    int numneighs = getLowestPossibilityNeighbourForCurrentPos(travelcount, travelled, neighs);
    if(numneighs == 0 && travelcount < BOARDWIDTH*BOARDWIDTH)
        {
            //std::cout<<"blocked, will go back, travelcount = "<<travelcount<<endl;
            travelled[travelcount-1] = -1;
            travelcount--;
            return travelcount;
        }
    
    for(int i = 0; i < numneighs; i++)
    {
        travelled[travelcount] = neighs[i];
        travelcount++;
        if(travelcount == BOARDWIDTH*BOARDWIDTH)
            return travelcount;
        travelcount = travel(travelcount, travelled);
        //std::cout<<"travel returns, travelcount = "<<travelcount<<endl;
        if(travelcount == BOARDWIDTH*BOARDWIDTH)
            return travelcount;
    }
    
    
    //std::cout<<"next travel = "<< travelled[travelcount - 1] <<endl;
    //std::cout<<"travelcount = "<<travelcount<<endl;
    return travelcount;
    
    
}
/**
 * for the current position, get the lowest possibility neighbour
 * input - an array of already travelled co-ordinates
 * output - position of lowest possibility neighbour or -1 if no neighbour found
 **/
int getLowestPossibilityNeighbourForCurrentPos(int travelcount, int travelled[], int freshneighs[])
{
    
    int currentpos = travelled[travelcount - 1];
    int y = currentpos/(BOARDWIDTH);
    int x = currentpos - y*(BOARDWIDTH);
    //std::cout<<"current pos is "<<" x = "<<x<<" y = "<<y<<endl;
    int arr[MAX_MOVES];
    int posneighs[MAX_MOVES];
    int num = getValidNeighbours(x, y, arr);
    int minneighbours = 8;
    int maxneighbours = 0;
    int pos_lowestneighbour = -1;
    int idx = 0;
    for(int i = 0; i < num; i++)
    {
        //First check if this is an empty neighbour
        if(!checkForFreshPosition(arr[i], travelcount, travelled) )
        {
            continue;
        }
        
        freshneighs[idx] = arr[i];
        int y1 = arr[i]/(BOARDWIDTH);
        int x1 = arr[i] - y1*(BOARDWIDTH);
        //This is the immediate neighbour
        // Now for this neighbour we get its valid neighbours and check if they 
        // not already in the travel array
        int neigh2[BOARDWIDTH];
        
        int num2 = getValidNeighbours(x1, y1, neigh2);
        int freshcount = 0;
        for(int j = 0; j < num2; j++)
        {
            if(checkForFreshPosition(neigh2[j], travelcount, travelled) )
                freshcount++;
        }
        posneighs[idx] = -1;
        for(int k = 0; k < idx; k++)
        {
            if(posneighs[k] > freshcount)
            {
                int val = posneighs[k];
                posneighs[k] = freshcount;
                int pos = freshneighs[k];
                freshneighs[k] = freshneighs[idx];
                for(int l = k+1; l<=idx; l++)
                {
                    int v = posneighs[l];
                    posneighs[l] = val;
                    val = v;
                    int p = freshneighs[l];
                    freshneighs[l] = pos;
                    pos = p;
                }
                
            }
        }
        if(posneighs[idx] == -1)
        {
            posneighs[idx] = freshcount;
        }
        

        
        idx++;
    }
    return idx;
}

/**
 * This function will check if the proposed position is already there in the travelled list
 * if its a fresh position, return true else return false
 */
bool checkForFreshPosition(int pos, int travelcount, int travelled[])
{
   
    for(int i = 0; i < travelcount; i++)
    {
        //std::cout<<"checking "<<pos<<" for fresh in "<<travelled[i]<<endl;
        if(pos == travelled[i])
            return false;
    }
    return true;
}