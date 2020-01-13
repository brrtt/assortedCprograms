//J Barrett Chesebrough
//ECE 209-051
//J Tuck
//Tracker works for all but part 9 and special cases of part 8

#include <stdio.h>
#include <math.h>
#ifndef SECRET_TESTS
double M1=-1.0, B1=0;
double M2=1.0, B2=0;
#else
double M1=SECRET_M1, B1=SECRET_B1;
double M2=SECRET_M2, B2=SECRET_B2;
#endif

double M1;
double B1;
double M2;
double B2;
int Road=1, First_road=1;
int Changed_direction=0;
int Changed_road=0;
double Total_distance=0.0;
double Peak_speed=0.0;
double prior_delta=0.0;
//Functions

double get_y(double x, int road){ //Find Y value corresponding to selectee x on selected road
	double y=0.0;
	if(road==1){
		y=M1*x+B1;
		}
	if(road==2){
		y=M2*x+B2;
		}
		
return y;
}

double x_intercept(void);

double distance(double x1, double y1, double x2, double y2){ //calculate distance using pythag. requires <math.h>
	double dist=0.0;
	double dx=x2-x1;
	double dy=y2-y1;
	double dx2=pow(dx,2);
	double dy2=pow(dy,2);
	dist=sqrt(dx2+dy2);
	
return dist;
}

double nearest_point_on_road(double x, double y, int road){ //calculates the y intercept of the selected road
	double b=0.0;
	double xx=0.0; //x'
	if(road==1){
		b=(1/M1)*x+y;
		xx=(b-B1)/(M1+(1/M1));		//permutation of point-slope notation to solve for nearest x on the line. 
	}
	if(road==2){
		b=(1/M2)*x+y;
		xx=(b-B2)/(M2+(1/M2));
	}
return xx;
}

int closest_road(double x, double y, int road){  //calls nearest_point_on_road to find closest road. 
	double dist1=0.0000;
	double dist2=0.0000;
	double x1=nearest_point_on_road(x,y,1);
	double y1=get_y(x1,1);
	double x2=nearest_point_on_road(x,y,2);
	double y2=get_y(x2,2);
	dist1=distance(x,y,x1,y1);
	dist2=distance(x,y,x2,y2);
	
	//printf("%lf /n",&dist1);
	//printf("%lf /n",&dist2);
	if(dist1<.0001 && dist2<.0001) return road; //special case conditions
	if(dist1>.0001 && dist2>.0001 && dist1==dist2) return road;
	else if(dist1>dist2) return 2;
	else if (dist2>dist1) return 1;
	else return road;
	}

double intercept(){ //unused
	double x=(B2-B1)/(M1-M2);
return x;
}

void track(double x, double y, double time){ //gives distance and speed correctly, changed_roads does not count correctly for all cases
	static int count=0;
	static double prior_x;
	double d=0.00000;
	double speed=0.00000;
	double delta=0.0;
	if(count==0){
		First_road=closest_road(x,y,Road);
		Road=First_road;
		prior_x=nearest_point_on_road(x,y,Road);
		//printf("count=0 check");
		}
	else{
		//printf("in else");
		d=distance(prior_x,get_y(prior_x,Road),nearest_point_on_road(x,y,Road),get_y(nearest_point_on_road(x,y,Road),Road));
		delta=x-prior_x;
		if(delta<0)Changed_direction++;
		prior_x=nearest_point_on_road(x,y,Road);
		prior_delta=delta;
		if(delta-prior_delta>0)Changed_direction++;
		//printf("dist calc");
		double speed=d/time;
		Total_distance+=d;
		//printf("speed calc");
		if(speed>Peak_speed) Peak_speed=speed;
		//printf("speed set");
	}
	
count++;
}

int main(){

double time, x, y;
int ret;
do {
	ret=scanf("%lf%lf%lf",&time,&x,&y); //get time,x,y -stdin
	if(ret==3){
		track(x,y,time);
		}
	} while(ret==3);

//printf("%d",&First_road);	
printf("Total distance = %.2lf\n",Total_distance);
printf("Peak speed = %.2lf\n",Peak_speed);
printf("# of changes in direction = %d\n",Changed_direction);
printf("# of changes in road = %d\n",Changed_road);
printf("First Road = %d, Last Road = %d\n",First_road,Road);
	
return 0;
}

