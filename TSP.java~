// Software: Visualization for solutions of Travelling Saleman Problem
// Author: Hy Truong Son
// Major: BSc. Computer Science
// Class: 2013 - 2016
// Institution: Eotvos Lorand University
// Email: sonpascal93@gmail.com
// Website: http://people.inf.elte.hu/hytruongson/
// Copyright 2015 (c) Hy Truong Son. All rights reserved. Use for academic purposes only.

import java.lang.*;
import java.io.*;
import java.awt.*;
import java.util.*;
import javax.swing.*;

import java.util.Random;
import java.awt.image.BufferedImage;
import javax.imageio.ImageIO;
import javax.imageio.ImageWriter;
import javax.imageio.stream.ImageOutputStream;

public class TSP {
	
	static int MaxN = 400;
	static String FileInput = "Graph.INP";
	static String ImageType = "bmp";
	
	static int width, height, n;
	static class point {
		public int x, y;
	}
	static point p[] = new point [MaxN];
	static int path[] = new int [MaxN];
	static BufferedImage image;
	static File file;
	
	public static int RGB(int red, int green, int blue){
		return (0xff000000) | (red << 16) | (green << 8) | blue;
	}
	
	public static String GetType(String FileName){
		int i, j;
		String res;
		j = 0;
		for (i = 0; i < FileName.length(); i++)
			if (FileName.charAt(i) == '.'){
				j = i;
				break;
			}
		res = "";
		for (i = j + 1; i < FileName.length(); i++) res += FileName.charAt(i);
		return res;
	}
	
	public static void input(String FileName) throws IOException{
		Scanner input = new Scanner(new File(FileName));
		width = input.nextInt();
		height = input.nextInt();
		n = input.nextInt();
		for (int i = 0; i < n; i++){
			p[i] = new point();
			p[i].x = input.nextInt();
			p[i].y = input.nextInt();
		}
	}
	
	public static void DrawLine_RED(int x1, int y1, int x2, int y2){
		Graphics2D g2d = image.createGraphics();
		g2d.setColor(Color.RED);
		g2d.drawLine(x1, y1, x2, y2);
	}
	
	public static void DrawPoint(int i, int j, int rgb) throws IOException{
		for (int u = -3; u <= 3; u++)
			for (int v = -3; v <= 3; v++){
				int x = i + u;
				int y = j + v;
				if ((x >= 0)&&(x < width)&&(y >= 0)&&(y < height))
					image.setRGB(x, y, rgb);
			}
	}
	
	public static void output(String FileName, String ImageName) throws IOException{
		Scanner output = new Scanner(new File(FileName));
		int res = output.nextInt();
		for (int i = 0; i < n; i++)
			path[i] = output.nextInt();
		
		image = new BufferedImage(width, height, BufferedImage.TYPE_INT_RGB);
		
		for (int i = 0; i < width; i++)
			for (int j = 0; j < height; j++)
				image.setRGB(i, j, RGB(255, 255, 255));
				
		for (int i = 0; i < n; i++){
			int x1 = p[path[i]].x;
			int y1 = p[path[i]].y;
			int x2 = p[path[(i + 1) % n]].x;
			int y2 = p[path[(i + 1) % n]].y;
			
			DrawLine_RED(x1, y1, x2, y2);
		}
		
		for (int i = 0; i < n; i++)
			DrawPoint(p[i].x, p[i].y, RGB(0, 255, 0));
		
		file = new File(ImageName);
		ImageIO.write(image, ImageType, file);
	}
	
	public static void main(String args[]) throws IOException{
		input(FileInput);
		output(args[0]+".OUT", args[0]+"."+ImageType);
	}

}
