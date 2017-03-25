#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/io/ply_io.h>
#include <pcl/io/vtk_lib_io.h>
#include <pcl/pcl_exports.h>

int  main (int argc, char** argv)
{
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // Code to Generate a random Point Cloud
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////
  /*pcl::PointCloud<pcl::PointXYZRGBNormal> cloud;
  //pcl::PLYReader cloud2;
  //cloud.read("CorvusEye_LowRes", cloud, 0);
  // Fill in the cloud data
  
  cloud.width    = 5;
  cloud.height   = 1;
  cloud.is_dense = false;
  cloud.points.resize (cloud.width * cloud.height);
 

  for (size_t i = 0; i < cloud.points.size (); ++i)
  {
    cloud.points[i].x = 1024 * rand () / (RAND_MAX + 1.0f);
    cloud.points[i].y = 1024 * rand () / (RAND_MAX + 1.0f);
    cloud.points[i].z = 1024 * rand () / (RAND_MAX + 1.0f);
  }

  pcl::io::savePLYFileASCII ("test_ply.ply", cloud);
  std::cerr << "Saved " << cloud.points.size () << " data points to test_ply.ply." << std::endl;

  for (size_t i = 0; i < cloud.points.size (); ++i)
    std::cerr << "    " << cloud.points[i].x << " " << cloud.points[i].y << " " << cloud.points[i].z << std::endl;
  /*
  */

  /*
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //Point Cloud with Colors and Normals
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  //pcl::PointCloud<pcl::PointXYZRGBNormal> cloud (new pcl::PointCloud<pcl::PointXYZRGBNormal>);
  
  //Point clouds to be used are created
  pcl::PointCloud<pcl::PointXYZ>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZ>);
  pcl::PointCloud<pcl::PointXYZ>::Ptr cloud2 (new pcl::PointCloud<pcl::PointXYZ>);

  //PLY file is being loaded
  if (pcl::io::loadPLYFile<pcl::PointXYZ>("airplane.ply", *cloud) == -1) //* load the file
  {
	//If file is not in the correct format
    PCL_ERROR ("Couldn't read file airplane.ply \n");
    std::cin.ignore();
	return (-1);
  }
  //if file is in the correct format
  std::cout << "Loaded "
            << cloud->width * cloud->height
            << " data points from airplane.ply with the following fields: "
            << std::endl;

  //Vectors that will hold the nearest points
  std::vector<pcl::PointXYZ> closestPoints;
  std::vector<double> closestDistances;
  double distance;
  
  //Analyzing which are the closest points of the loaded point cloud to the origin
  for (int i = 0; i < cloud->points.size (); i++){
    distance = sqrt(pow(cloud->points[i].x - 896.966, 2) + cloud->points[i].y * cloud->points[i].y + cloud->points[i].z * cloud->points[i].z);
	if (distance < 300){
      //closestDistances.push_back(distance);
	  closestPoints.push_back(cloud->points[i]);
	}
	//if (closestDistances.at(0) > distance){
	  
	//  closestDistances.at(0) = distance;
	//}
    std::cout << "    " << cloud->points[i].x
              << " "    << cloud->points[i].y
              << " "    << cloud->points[i].z
			  << " "    << cloud->points[i].data << std::endl;
  }

  //Adding closests points to 2nd point cloud
  for(int j = 0; j < closestPoints.size(); j++){
	  cloud2->points.push_back(closestPoints.at(j));
  }

  //Saving 2nd Point Cloud with Closest Points
  pcl::io::savePLYFileASCII<pcl::PointXYZ>("airplaneface.ply", *cloud2);

  /////////////////////////////////////////////////////////////////////////////////////////////////////
  //std::cout << "The shortest distance to origin is " << closest.at(0) << std::endl;

  */

  /*
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //Testing point LoS validation
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  //Point cloud object to be used
  pcl::PointCloud<pcl::PointXYZ>::Ptr cloud3 (new pcl::PointCloud<pcl::PointXYZ>);

  //Creating Points
  pcl::PointXYZ p1, p2, p3;
  p1.x = 1;
  p1.y = 1;
  p1.z = 1;

  p2.x = 2;
  p2.y = 2;
  p2.z = 2;

  p3.x = 1;
  p3.y = 3;
  p3.z = 3;
  
  //Creating slope variables and the slope from the origin
  float mXY, mXZ, mYZ, tempMXY, tempMXZ, tempMYZ;
  mXY = p1.y/p1.x;
  mXZ = p1.z/p1.x;
  mYZ = p1.z/p1.y;

  cloud3->points.push_back(p2);
  cloud3->points.push_back(p3);

  for(int i = 0; i < cloud3->points.size(); i++){
	tempMXY = cloud3->points[i].y/cloud3->points[i].x;
    tempMXZ = cloud3->points[i].z/cloud3->points[i].x;
    tempMYZ = cloud3->points[i].z/cloud3->points[i].y;
	  if(mXY == tempMXY && mXZ == tempMXZ && mYZ == tempMYZ){
		  std::cout << "The point " << cloud3->points[i].x 
		  << " " << cloud3->points[i].y
		  << " " << cloud3->points[i].z
		  << " obstructs the line of sight of" << std::endl;
	  }
  }
  */


  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //LOS Line Tracing
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  //*

  //Get input for file names.
  std::string fileName1;
  std::string fileName2;

  std::cout << "Please, enter name of first file: ";
  std::getline (std::cin,fileName1);
  std::cout << "Please, enter name of second file: ";
  std::getline (std::cin,fileName2);

  //Point clouds objects to be used are created
  pcl::PointCloud<pcl::PointXYZRGB>::Ptr object_cloud (new pcl::PointCloud<pcl::PointXYZRGB>);
  pcl::PointCloud<pcl::PointXYZRGB>::Ptr obstruction_cloud (new pcl::PointCloud<pcl::PointXYZRGB>);

  //File names
  std::string resultNumber = "los_result39"; //Resulting PLY file name
  std::string lastChange = "adding_point_of_analysis"; // Last change in the code
  // std::string fileName1 = "airplane";  //Object point cloud file name
  // std::string fileName2 = "wall_with_hole";	   //Obstruction point cloud file name

  //First PLY file is being loaded
  if (pcl::io::loadPLYFile<pcl::PointXYZRGB>(fileName1 + ".ply", *object_cloud) == -1) //* load the file
  {
	//If file is not in the correct format
    PCL_ERROR ("Couldn't read first .ply file \n");
	return (-1);
  }
  //If file is in the correct format
  std::cout << "Loaded "
			<< object_cloud->width * object_cloud->height
            << " data points from " + fileName1 + ".ply"
            << std::endl;

  //Second PLY file is being loaded
  if (pcl::io::loadPLYFile<pcl::PointXYZRGB>(fileName2 + ".ply", *obstruction_cloud) == -1) //* load the file
  {
	//If file is not in the correct format
    PCL_ERROR ("Couldn't read second .ply file\n");
	return (-1);
  }
  //if file is in the correct format
  std::cout << "Loaded "
            << obstruction_cloud->width * obstruction_cloud->height
            << " data points from " + fileName2 + ".ply"
            << std::endl;

  //Line Tracing variable definition
  int mXY, mXZ, mYZ, tempMXY, tempMXZ, tempMYZ; //Slope Variables
  int objectDistance, obstructionDistance;		//Distance Variables
  double EPSILON = std::numeric_limits<double>::epsilon(); //Epsilon value (used for float threshold value)
  int counter = 0;								//Obstruction counter
  pcl::PointXYZRGB pO;								//Point of analysis initialization
  //Point Position
  pO.x = -2000.0; //before: -250
  pO.y = 25.0;
  pO.z = 60.0;
  //Point Color
  pO.r = 0;
  pO.g = 255;
  pO.b = 0;

  double accuracy = 0.000001;					//Helping value that avoids error from divisions by 0
  int precision = 10;							//Precision value (used for int threshold value)

 

  //Log file creation
  std::ofstream logFile;
  logFile.open ("log_" + resultNumber + "_" + fileName1 + "_with_" + fileName2 + "_" + lastChange + ".txt");

  //Write point of analysis
  logFile << "The point of analysis is " << pO.x << " " << pO.y << " " << pO.z << "\n" <<endl;

  for(int i = 0; i < object_cloud->points.size(); i++){
    //pcl::PointXYZRGB object_point = &object_cloud->points[i]; //current object point (couldnt create the pointer, working in this)
	  //Object Point distance to Point of Analysis
	  objectDistance = sqrt((1000)*pow(object_cloud->points[i].x - pO.x, 2) + pow((1000)*object_cloud->points[i].y - pO.y, 2) + pow((1000)*object_cloud->points[i].z - pO.z, 2)); //Object point distance from point of analysis is calculated
	  //Object Point Slopes
	  mXY = 1000*((object_cloud->points[i].y - pO.y + accuracy)/(object_cloud->points[i].x - pO.x + accuracy));	//Object point XY slope
    mXZ = 1000*((object_cloud->points[i].z - pO.z + accuracy)/(object_cloud->points[i].x - pO.x + accuracy));	//Object point XZ slope
    mYZ = 1000*((object_cloud->points[i].z - pO.z + accuracy)/(object_cloud->points[i].y - pO.y + accuracy));	//Object point YZ slope
	  for(int j = 0; j < obstruction_cloud->points.size();j++){
		  //pcl::PointXYZRGB obtruction_point = obstruction_cloud->points[j]; //current obstruction point
		  //Obstruction Point distance to Point of Analysis
		  obstructionDistance = sqrt((1000)*pow(obstruction_cloud->points[j].x - pO.x, 2) + pow((1000)*obstruction_cloud->points[j].y - pO.y, 2) + pow((1000)*obstruction_cloud->points[j].z - pO.z, 2)); //Obstruction point distance from point of analysis is calculated
	    //Obstruction Point Slopes
		  tempMXY = 1000*((obstruction_cloud->points[j].y - pO.y + accuracy)/(obstruction_cloud->points[j].x - pO.x + accuracy));	//Obstruction point XY slope
      tempMXZ = 1000*((obstruction_cloud->points[j].z - pO.z + accuracy)/(obstruction_cloud->points[j].x - pO.x + accuracy));	//Obstruction point XZ slope
      tempMYZ = 1000*((obstruction_cloud->points[j].z - pO.z + accuracy)/(obstruction_cloud->points[j].y - pO.y + accuracy));	//Obstruction point YZ slope

	    //If obstruction slope values are close enough to the object slope values and its distance is smaller then it is considered an obstruction
		  if((abs(mXY - tempMXY) < precision) && (abs(mXZ - tempMXZ) < precision) && (abs(mYZ - tempMYZ) < precision) && (obstructionDistance <= objectDistance)){
		    counter++;	//Obstruction Counter
		    object_cloud->points[i].r = 255; //An obstruction is colored red to be able to visualize it in cloud compare
		    object_cloud->points[i].g = 0;
		    object_cloud->points[i].b = 0;

		    //A log file is written with the results of each obstruction
		    logFile << counter << "- The point " << obstruction_cloud->points[j].x     //First, the coordinates are written
		                       << " " << obstruction_cloud->points[j].y
		                       << " " << obstruction_cloud->points[j].z
		                       << " is obstructing " << object_cloud->points[i].x 
		                       << " " << object_cloud->points[i].y
		                       << " " << object_cloud->points[i].z << std::endl;

		    logFile << "The object slopes are " << mXY << " " << mXZ	<< " " << mYZ					       //After, the slope values calculated
				        << " and obstruction" << tempMXY << " " << tempMXZ << " " << tempMYZ << "\n" << std::endl;
		                     
		    break; //Since the current point is considered obstructed no further analysis with respect to this point is needed
	    }
		  else{
		    object_cloud->points[i].r = 255;
		    object_cloud->points[i].g = 255;
		    object_cloud->points[i].b = 255;
		  }

	  }
  }

  //Add point of analysis
  object_cloud->points.push_back(pO);
  object_cloud->width++;


  //Information about the analysis is printed
  std::cout << "\nPoint of Analysis: " << pO.x << " " << pO.y << " " << pO.z << endl;
  std::cout << "Number of Points: " << object_cloud->points.size() << std::endl;   //Total of points in the object point cloud
  std::cout << "Number of Obstructions: " << counter << std::endl;			//Total of obstructed points of the object point cloud
  std::cout << "Percentage of Sight: " << ((double)1 - ((double)counter/(double)object_cloud->points.size()))*(double)100 << "%" << std::endl; //Percentage of visibility of the point cloud
  
  
  //Saving colored edited Point Cloud
  pcl::io::savePLYFileASCII<pcl::PointXYZRGB>(resultNumber + "_" + fileName1 + "_with_" + fileName2 + "_" + lastChange + ".ply", *object_cloud);
  std::cout << "Point Cloud with obstructions was successfully saved" << std::endl;

  //Closing log file
  logFile.close();
  std::cout << "Log for " + resultNumber + " was successfully written" << std::endl;
  //*/

 
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //Point Cloud Generation
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  /*
  //Point clouds to be used are created
  pcl::PointCloud<pcl::PointXYZ>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZ>);
  //pcl::PointCloud<pcl::PointXYZ>::Ptr cloud2 (new pcl::PointCloud<pcl::PointXYZ>);

  //*
  //Definition of a point
  pcl::PointXYZ point;

  //Size of the point cloud dimensions
  int sizeX = 1;
  int sizeY = 150;
  int sizeZ = 150;

  //Displacement of the point cloud from origin
  int displacementX = -150;
  int displacementY = -50;
  int displacementZ = 0;

  //Generating points
  std::cout << "Generation of " << sizeX * sizeY * sizeZ << " points has begun" << std::endl;
  for(int z = 0; z < sizeZ; z++)
	  for(int y = 0; y < sizeY; y++)
		  //if(z > 73){
		  for(int x = 0; x < sizeX; x++){
			  point.x = x + displacementX;
			  point.y = y + displacementY;
			  point.z = z + displacementZ;
			  cloud->points.push_back(point); //After setting the correct values point is added to the points vector of the point cloud object
		 // }
		  }

  //Saving Point Cloud
  pcl::io::savePLYFileASCII<pcl::PointXYZ>("wall_for_sphere.ply", *cloud);
  std::cout << "Point Cloud was successfully generated" << std::endl;

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //Point Cloud Point Transfer
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  /*
  //First PLY file is being loaded
  if (pcl::io::loadPLYFile<pcl::PointXYZ>("cube_face.ply", *cloud) == -1) //* load the file
  {
	//If file is not in the correct format
    PCL_ERROR ("Couldn't read file cube_face.ply \n");
	return (-1);
  }
  //if file is in the correct format
  std::cout << "Loaded "
			<< cloud->width * cloud->height
            << " data points from cube_face.ply with the following fields: "
            << std::endl;

  //Second PLY file is being loaded
  
  if (pcl::io::loadPLYFile<pcl::PointXYZ>("wall.ply", *cloud2) == -1) //* load the file
  {
	//If file is not in the correct format
    PCL_ERROR ("Couldn't read file wall.ply \n");
	return (-1);
  }
  //if file is in the correct format
  std::cout << "Loaded "
            << cloud->width * cloud->height
            << " data points from wall.ply with the following fields: "
            << std::endl;

  //Passing the points from one point cloud to the other
  for(int i = 0; i < cloud2->points.size(); i++){
    cloud->points.push_back(cloud2->points[i]);
	cloud->width++; //Its width value must be increased to the current points vector size;
  }

  //Saving combined Point Cloud 
  pcl::io::savePLYFileASCII<pcl::PointXYZ>("cube_face_with_wall.ply", *cloud);
  std::cout << "Point Cloud was successfully modified" << std::endl;

  */
  return(0);
  
}