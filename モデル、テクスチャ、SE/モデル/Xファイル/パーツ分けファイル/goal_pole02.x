xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 98;
 0.00000;156.88074;-13.19234;,
 3.38815;156.88074;-12.74622;,
 3.38815;-0.01559;-12.74622;,
 0.00000;-0.01559;-13.19234;,
 6.54541;156.88074;-11.43846;,
 6.54541;-0.01559;-11.43846;,
 9.25661;156.88074;-9.35815;,
 9.25661;-0.01559;-9.35815;,
 11.33698;156.88074;-6.64683;,
 11.33698;-0.01559;-6.64683;,
 12.64476;156.88074;-3.48965;,
 12.64476;-0.01559;-3.48965;,
 13.09082;156.88074;-0.10148;,
 13.09082;-0.01559;-0.10148;,
 12.64476;156.88074;3.28666;,
 12.64476;-0.01559;3.28666;,
 11.33698;156.88074;6.44393;,
 11.33698;-0.01559;6.44393;,
 9.25661;156.88074;9.15507;,
 9.25661;-0.01559;9.15507;,
 6.54541;156.88074;11.23543;,
 6.54541;-0.01559;11.23543;,
 3.38815;156.88074;12.54330;,
 3.38815;-0.01559;12.54330;,
 0.00000;156.88074;12.98929;,
 0.00000;-0.01559;12.98929;,
 -3.38815;156.88074;12.54330;,
 -3.38815;-0.01559;12.54330;,
 -6.54541;156.88074;11.23543;,
 -6.54541;-0.01559;11.23543;,
 -9.25661;156.88074;9.15516;,
 -9.25661;-0.01559;9.15516;,
 -11.33698;156.88074;6.44393;,
 -11.33698;-0.01559;6.44393;,
 -12.64476;156.88074;3.28666;,
 -12.64476;-0.01559;3.28666;,
 -13.09082;156.88074;-0.10143;,
 -13.09082;-0.01559;-0.10143;,
 -12.64476;156.88074;-3.48965;,
 -12.64476;-0.01559;-3.48965;,
 -11.33698;156.88074;-6.64683;,
 -11.33698;-0.01559;-6.64683;,
 -9.25664;156.88074;-9.35815;,
 -9.25664;-0.01559;-9.35815;,
 -6.54541;156.88074;-11.43846;,
 -6.54541;-0.01559;-11.43846;,
 -3.38815;156.88074;-12.74622;,
 -3.38815;-0.01559;-12.74622;,
 0.00000;156.88074;-13.19234;,
 0.00000;-0.01559;-13.19234;,
 0.00000;156.88074;-0.10148;,
 0.00000;156.88074;-0.10148;,
 0.00000;156.88074;-0.10148;,
 0.00000;156.88074;-0.10148;,
 0.00000;156.88074;-0.10148;,
 0.00000;156.88074;-0.10148;,
 0.00000;156.88074;-0.10148;,
 0.00000;156.88074;-0.10148;,
 0.00000;156.88074;-0.10148;,
 0.00000;156.88074;-0.10148;,
 0.00000;156.88074;-0.10148;,
 0.00000;156.88074;-0.10148;,
 0.00000;156.88074;-0.10148;,
 0.00000;156.88074;-0.10148;,
 0.00000;156.88074;-0.10148;,
 0.00000;156.88074;-0.10148;,
 0.00000;156.88074;-0.10148;,
 0.00000;156.88074;-0.10148;,
 0.00000;156.88074;-0.10148;,
 0.00000;156.88074;-0.10148;,
 0.00000;156.88074;-0.10148;,
 0.00000;156.88074;-0.10148;,
 0.00000;156.88074;-0.10148;,
 0.00000;156.88074;-0.10148;,
 0.00000;-0.01559;-0.10148;,
 0.00000;-0.01559;-0.10148;,
 0.00000;-0.01559;-0.10148;,
 0.00000;-0.01559;-0.10148;,
 0.00000;-0.01559;-0.10148;,
 0.00000;-0.01559;-0.10148;,
 0.00000;-0.01559;-0.10148;,
 0.00000;-0.01559;-0.10148;,
 0.00000;-0.01559;-0.10148;,
 0.00000;-0.01559;-0.10148;,
 0.00000;-0.01559;-0.10148;,
 0.00000;-0.01559;-0.10148;,
 0.00000;-0.01559;-0.10148;,
 0.00000;-0.01559;-0.10148;,
 0.00000;-0.01559;-0.10148;,
 0.00000;-0.01559;-0.10148;,
 0.00000;-0.01559;-0.10148;,
 0.00000;-0.01559;-0.10148;,
 0.00000;-0.01559;-0.10148;,
 0.00000;-0.01559;-0.10148;,
 0.00000;-0.01559;-0.10148;,
 0.00000;-0.01559;-0.10148;,
 0.00000;-0.01559;-0.10148;,
 0.00000;-0.01559;-0.10148;;
 
 72;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;6,8,9,7;,
 4;8,10,11,9;,
 4;10,12,13,11;,
 4;12,14,15,13;,
 4;14,16,17,15;,
 4;16,18,19,17;,
 4;18,20,21,19;,
 4;20,22,23,21;,
 4;22,24,25,23;,
 4;24,26,27,25;,
 4;26,28,29,27;,
 4;28,30,31,29;,
 4;30,32,33,31;,
 4;32,34,35,33;,
 4;34,36,37,35;,
 4;36,38,39,37;,
 4;38,40,41,39;,
 4;40,42,43,41;,
 4;42,44,45,43;,
 4;44,46,47,45;,
 4;46,48,49,47;,
 3;50,1,0;,
 3;51,4,1;,
 3;52,6,4;,
 3;53,8,6;,
 3;54,10,8;,
 3;55,12,10;,
 3;56,14,12;,
 3;57,16,14;,
 3;58,18,16;,
 3;59,20,18;,
 3;60,22,20;,
 3;61,24,22;,
 3;62,26,24;,
 3;63,28,26;,
 3;64,30,28;,
 3;65,32,30;,
 3;66,34,32;,
 3;67,36,34;,
 3;68,38,36;,
 3;69,40,38;,
 3;70,42,40;,
 3;71,44,42;,
 3;72,46,44;,
 3;73,48,46;,
 3;74,3,2;,
 3;75,2,5;,
 3;76,5,7;,
 3;77,7,9;,
 3;78,9,11;,
 3;79,11,13;,
 3;80,13,15;,
 3;81,15,17;,
 3;82,17,19;,
 3;83,19,21;,
 3;84,21,23;,
 3;85,23,25;,
 3;86,25,27;,
 3;87,27,29;,
 3;88,29,31;,
 3;89,31,33;,
 3;90,33,35;,
 3;91,35,37;,
 3;92,37,39;,
 3;93,39,41;,
 3;94,41,43;,
 3;95,43,45;,
 3;96,45,47;,
 3;97,47,49;;
 
 MeshMaterialList {
  3;
  72;
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "C:\\Users\\student\\Desktop\\ゲーム制作用\\goal.png";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.009600;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  26;
  0.000000;1.000000;0.000000;,
  0.000000;0.000000;-1.000000;,
  0.258825;0.000000;-0.965924;,
  0.499991;0.000000;-0.866031;,
  0.707109;0.000000;-0.707104;,
  0.866029;0.000000;-0.499994;,
  0.965925;0.000000;-0.258823;,
  1.000000;0.000000;0.000001;,
  0.965926;0.000000;0.258819;,
  0.866023;0.000000;0.500004;,
  0.707102;0.000000;0.707111;,
  0.500009;0.000000;0.866020;,
  0.258821;0.000000;0.965925;,
  0.000000;0.000000;1.000000;,
  -0.258821;0.000000;0.965925;,
  -0.500000;0.000000;0.866026;,
  -0.707101;0.000000;0.707113;,
  -0.866027;0.000000;0.499997;,
  -0.965926;0.000000;0.258820;,
  -1.000000;0.000000;0.000002;,
  -0.965925;0.000000;-0.258822;,
  -0.866031;0.000000;-0.499991;,
  -0.707110;0.000000;-0.707104;,
  -0.499989;0.000000;-0.866032;,
  -0.258825;0.000000;-0.965924;,
  0.000000;-1.000000;-0.000000;;
  72;
  4;1,2,2,1;,
  4;2,3,3,2;,
  4;3,4,4,3;,
  4;4,5,5,4;,
  4;5,6,6,5;,
  4;6,7,7,6;,
  4;7,8,8,7;,
  4;8,9,9,8;,
  4;9,10,10,9;,
  4;10,11,11,10;,
  4;11,12,12,11;,
  4;12,13,13,12;,
  4;13,14,14,13;,
  4;14,15,15,14;,
  4;15,16,16,15;,
  4;16,17,17,16;,
  4;17,18,18,17;,
  4;18,19,19,18;,
  4;19,20,20,19;,
  4;20,21,21,20;,
  4;21,22,22,21;,
  4;22,23,23,22;,
  4;23,24,24,23;,
  4;24,1,1,24;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;25,25,25;,
  3;25,25,25;,
  3;25,25,25;,
  3;25,25,25;,
  3;25,25,25;,
  3;25,25,25;,
  3;25,25,25;,
  3;25,25,25;,
  3;25,25,25;,
  3;25,25,25;,
  3;25,25,25;,
  3;25,25,25;,
  3;25,25,25;,
  3;25,25,25;,
  3;25,25,25;,
  3;25,25,25;,
  3;25,25,25;,
  3;25,25,25;,
  3;25,25,25;,
  3;25,25,25;,
  3;25,25,25;,
  3;25,25,25;,
  3;25,25,25;,
  3;25,25,25;;
 }
 MeshTextureCoords {
  98;
  0.000000;0.000000;,
  0.041670;0.000000;,
  0.041670;1.000000;,
  0.000000;1.000000;,
  0.083330;0.000000;,
  0.083330;1.000000;,
  0.125000;0.000000;,
  0.125000;1.000000;,
  0.166670;0.000000;,
  0.166670;1.000000;,
  0.208330;0.000000;,
  0.208330;1.000000;,
  0.250000;0.000000;,
  0.250000;1.000000;,
  0.291670;0.000000;,
  0.291670;1.000000;,
  0.333330;0.000000;,
  0.333330;1.000000;,
  0.375000;0.000000;,
  0.375000;1.000000;,
  0.416670;0.000000;,
  0.416670;1.000000;,
  0.458330;0.000000;,
  0.458330;1.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.541670;0.000000;,
  0.541670;1.000000;,
  0.583330;0.000000;,
  0.583330;1.000000;,
  0.625000;0.000000;,
  0.625000;1.000000;,
  0.666670;0.000000;,
  0.666670;1.000000;,
  0.708330;0.000000;,
  0.708330;1.000000;,
  0.750000;0.000000;,
  0.750000;1.000000;,
  0.791670;0.000000;,
  0.791670;1.000000;,
  0.833330;0.000000;,
  0.833330;1.000000;,
  0.875000;0.000000;,
  0.875000;1.000000;,
  0.916670;0.000000;,
  0.916670;1.000000;,
  0.958330;0.000000;,
  0.958330;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.020830;0.000000;,
  0.062500;0.000000;,
  0.104170;0.000000;,
  0.145830;0.000000;,
  0.187500;0.000000;,
  0.229170;0.000000;,
  0.270830;0.000000;,
  0.312500;0.000000;,
  0.354170;0.000000;,
  0.395830;0.000000;,
  0.437500;0.000000;,
  0.479170;0.000000;,
  0.520830;0.000000;,
  0.562500;0.000000;,
  0.604170;0.000000;,
  0.645830;0.000000;,
  0.687500;0.000000;,
  0.729170;0.000000;,
  0.770830;0.000000;,
  0.812500;0.000000;,
  0.854170;0.000000;,
  0.895830;0.000000;,
  0.937500;0.000000;,
  0.979170;0.000000;,
  0.020830;1.000000;,
  0.062500;1.000000;,
  0.104170;1.000000;,
  0.145830;1.000000;,
  0.187500;1.000000;,
  0.229170;1.000000;,
  0.270830;1.000000;,
  0.312500;1.000000;,
  0.354170;1.000000;,
  0.395830;1.000000;,
  0.437500;1.000000;,
  0.479170;1.000000;,
  0.520830;1.000000;,
  0.562500;1.000000;,
  0.604170;1.000000;,
  0.645830;1.000000;,
  0.687500;1.000000;,
  0.729170;1.000000;,
  0.770830;1.000000;,
  0.812500;1.000000;,
  0.854170;1.000000;,
  0.895830;1.000000;,
  0.937500;1.000000;,
  0.979170;1.000000;;
 }
}
