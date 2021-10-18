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
 158;
 3.68007;5.64498;-6.90201;,
 4.25181;5.47807;-7.35796;,
 3.68007;5.47807;-7.63329;,
 3.68007;5.64498;-6.90201;,
 4.39302;5.47807;-6.73928;,
 3.68007;5.64498;-6.90201;,
 3.99736;5.47807;-6.24314;,
 3.68007;5.64498;-6.90201;,
 3.36277;5.47807;-6.24314;,
 3.68007;5.64498;-6.90201;,
 2.96711;5.47807;-6.73928;,
 3.68007;5.64498;-6.90201;,
 3.10832;5.47807;-7.35796;,
 3.68007;5.64498;-6.90201;,
 3.68007;5.47807;-7.63329;,
 4.71031;5.01039;-7.72360;,
 3.68007;5.01039;-8.21974;,
 4.96476;5.01039;-6.60878;,
 4.25181;5.01039;-5.71477;,
 3.10832;5.01039;-5.71477;,
 2.39536;5.01039;-6.60878;,
 2.64981;5.01039;-7.72360;,
 3.68007;5.01039;-8.21974;,
 4.96476;4.33458;-7.92652;,
 3.68007;4.33458;-8.54520;,
 5.28206;4.33458;-6.53636;,
 4.39302;4.33458;-5.42154;,
 2.96711;4.33458;-5.42154;,
 2.07807;4.33458;-6.53636;,
 2.39536;4.33458;-7.92652;,
 3.68007;4.33458;-8.54520;,
 4.96476;3.58448;-7.92652;,
 3.68007;3.58448;-8.54520;,
 5.28206;3.58448;-6.53636;,
 4.39302;3.58448;-5.42154;,
 2.96711;3.58448;-5.42154;,
 2.07807;3.58448;-6.53636;,
 2.39536;3.58448;-7.92652;,
 3.68007;3.58448;-8.54520;,
 4.71031;2.90867;-7.72360;,
 3.68007;2.90867;-8.21974;,
 4.96476;2.90867;-6.60878;,
 4.25181;2.90867;-5.71477;,
 3.10832;2.90867;-5.71477;,
 2.39536;2.90867;-6.60878;,
 2.64981;2.90867;-7.72360;,
 3.68007;2.90867;-8.21974;,
 4.25181;2.44099;-7.35796;,
 3.68007;2.44099;-7.63329;,
 4.39302;2.44099;-6.73928;,
 3.99736;2.44099;-6.24314;,
 3.36277;2.44099;-6.24314;,
 2.96711;2.44099;-6.73928;,
 3.10832;2.44099;-7.35796;,
 3.68007;2.44099;-7.63329;,
 3.68007;2.27408;-6.90201;,
 3.68007;2.27408;-6.90201;,
 3.68007;2.27408;-6.90201;,
 3.68007;2.27408;-6.90201;,
 3.68007;2.27408;-6.90201;,
 3.68007;2.27408;-6.90201;,
 3.68007;2.27408;-6.90201;,
 0.00000;11.48352;-10.54219;,
 7.46985;11.48352;-7.44807;,
 4.86441;-0.06609;-4.84264;,
 0.00000;-0.06609;-6.85754;,
 10.56396;11.48352;0.02177;,
 6.87931;-0.06609;0.02177;,
 7.46985;11.48352;7.49162;,
 4.86441;-0.06609;4.88618;,
 -0.00000;11.48352;10.58573;,
 -0.00000;-0.06609;6.90109;,
 -7.46985;11.48352;7.49162;,
 -4.86441;-0.06609;4.88618;,
 -10.56396;11.48352;0.02177;,
 -6.87931;-0.06609;0.02177;,
 -7.46985;11.48352;-7.44807;,
 -4.86441;-0.06609;-4.84264;,
 0.00000;11.48352;-10.54219;,
 0.00000;-0.06609;-6.85754;,
 0.00000;11.48352;0.02177;,
 0.00000;11.48352;0.02177;,
 0.00000;11.48352;0.02177;,
 0.00000;11.48352;0.02177;,
 0.00000;11.48352;0.02177;,
 0.00000;11.48352;0.02177;,
 0.00000;11.48352;0.02177;,
 0.00000;11.48352;0.02177;,
 0.00000;-0.06609;0.02177;,
 0.00000;-0.06609;0.02177;,
 0.00000;-0.06609;0.02177;,
 0.00000;-0.06609;0.02177;,
 0.00000;-0.06609;0.02177;,
 0.00000;-0.06609;0.02177;,
 0.00000;-0.06609;0.02177;,
 0.00000;-0.06609;0.02177;,
 -3.44152;5.64498;-6.90201;,
 -2.86977;5.47807;-7.35796;,
 -3.44152;5.47807;-7.63329;,
 -3.44152;5.64498;-6.90201;,
 -2.72857;5.47807;-6.73928;,
 -3.44152;5.64498;-6.90201;,
 -3.12422;5.47807;-6.24314;,
 -3.44152;5.64498;-6.90201;,
 -3.75881;5.47807;-6.24314;,
 -3.44152;5.64498;-6.90201;,
 -4.15447;5.47807;-6.73928;,
 -3.44152;5.64498;-6.90201;,
 -4.01326;5.47807;-7.35796;,
 -3.44152;5.64498;-6.90201;,
 -3.44152;5.47807;-7.63329;,
 -2.41127;5.01039;-7.72360;,
 -3.44152;5.01039;-8.21974;,
 -2.15682;5.01039;-6.60878;,
 -2.86977;5.01039;-5.71477;,
 -4.01326;5.01039;-5.71477;,
 -4.72622;5.01039;-6.60878;,
 -4.47177;5.01039;-7.72360;,
 -3.44152;5.01039;-8.21974;,
 -2.15682;4.33458;-7.92652;,
 -3.44152;4.33458;-8.54520;,
 -1.83953;4.33458;-6.53636;,
 -2.72857;4.33458;-5.42154;,
 -4.15447;4.33458;-5.42154;,
 -5.04351;4.33458;-6.53636;,
 -4.72622;4.33458;-7.92652;,
 -3.44152;4.33458;-8.54520;,
 -2.15682;3.58448;-7.92652;,
 -3.44152;3.58448;-8.54520;,
 -1.83953;3.58448;-6.53636;,
 -2.72857;3.58448;-5.42154;,
 -4.15447;3.58448;-5.42154;,
 -5.04351;3.58448;-6.53636;,
 -4.72622;3.58448;-7.92652;,
 -3.44152;3.58448;-8.54520;,
 -2.41127;2.90867;-7.72360;,
 -3.44152;2.90867;-8.21974;,
 -2.15682;2.90867;-6.60878;,
 -2.86977;2.90867;-5.71477;,
 -4.01326;2.90867;-5.71477;,
 -4.72622;2.90867;-6.60878;,
 -4.47177;2.90867;-7.72360;,
 -3.44152;2.90867;-8.21974;,
 -2.86977;2.44099;-7.35796;,
 -3.44152;2.44099;-7.63329;,
 -2.72857;2.44099;-6.73928;,
 -3.12422;2.44099;-6.24314;,
 -3.75881;2.44099;-6.24314;,
 -4.15447;2.44099;-6.73928;,
 -4.01326;2.44099;-7.35796;,
 -3.44152;2.44099;-7.63329;,
 -3.44152;2.27408;-6.90201;,
 -3.44152;2.27408;-6.90201;,
 -3.44152;2.27408;-6.90201;,
 -3.44152;2.27408;-6.90201;,
 -3.44152;2.27408;-6.90201;,
 -3.44152;2.27408;-6.90201;,
 -3.44152;2.27408;-6.90201;;
 
 122;
 3;0,1,2;,
 3;3,4,1;,
 3;5,6,4;,
 3;7,8,6;,
 3;9,10,8;,
 3;11,12,10;,
 3;13,14,12;,
 4;2,1,15,16;,
 4;1,4,17,15;,
 4;4,6,18,17;,
 4;6,8,19,18;,
 4;8,10,20,19;,
 4;10,12,21,20;,
 4;12,14,22,21;,
 4;16,15,23,24;,
 4;15,17,25,23;,
 4;17,18,26,25;,
 4;18,19,27,26;,
 4;19,20,28,27;,
 4;20,21,29,28;,
 4;21,22,30,29;,
 4;24,23,31,32;,
 4;23,25,33,31;,
 4;25,26,34,33;,
 4;26,27,35,34;,
 4;27,28,36,35;,
 4;28,29,37,36;,
 4;29,30,38,37;,
 4;32,31,39,40;,
 4;31,33,41,39;,
 4;33,34,42,41;,
 4;34,35,43,42;,
 4;35,36,44,43;,
 4;36,37,45,44;,
 4;37,38,46,45;,
 4;40,39,47,48;,
 4;39,41,49,47;,
 4;41,42,50,49;,
 4;42,43,51,50;,
 4;43,44,52,51;,
 4;44,45,53,52;,
 4;45,46,54,53;,
 3;48,47,55;,
 3;47,49,56;,
 3;49,50,57;,
 3;50,51,58;,
 3;51,52,59;,
 3;52,53,60;,
 3;53,54,61;,
 4;62,63,64,65;,
 4;63,66,67,64;,
 4;66,68,69,67;,
 4;68,70,71,69;,
 4;70,72,73,71;,
 4;72,74,75,73;,
 4;74,76,77,75;,
 4;76,78,79,77;,
 3;80,63,62;,
 3;81,66,63;,
 3;82,68,66;,
 3;83,70,68;,
 3;84,72,70;,
 3;85,74,72;,
 3;86,76,74;,
 3;87,78,76;,
 3;88,65,64;,
 3;89,64,67;,
 3;90,67,69;,
 3;91,69,71;,
 3;92,71,73;,
 3;93,73,75;,
 3;94,75,77;,
 3;95,77,79;,
 3;96,97,98;,
 3;99,100,97;,
 3;101,102,100;,
 3;103,104,102;,
 3;105,106,104;,
 3;107,108,106;,
 3;109,110,108;,
 4;98,97,111,112;,
 4;97,100,113,111;,
 4;100,102,114,113;,
 4;102,104,115,114;,
 4;104,106,116,115;,
 4;106,108,117,116;,
 4;108,110,118,117;,
 4;112,111,119,120;,
 4;111,113,121,119;,
 4;113,114,122,121;,
 4;114,115,123,122;,
 4;115,116,124,123;,
 4;116,117,125,124;,
 4;117,118,126,125;,
 4;120,119,127,128;,
 4;119,121,129,127;,
 4;121,122,130,129;,
 4;122,123,131,130;,
 4;123,124,132,131;,
 4;124,125,133,132;,
 4;125,126,134,133;,
 4;128,127,135,136;,
 4;127,129,137,135;,
 4;129,130,138,137;,
 4;130,131,139,138;,
 4;131,132,140,139;,
 4;132,133,141,140;,
 4;133,134,142,141;,
 4;136,135,143,144;,
 4;135,137,145,143;,
 4;137,138,146,145;,
 4;138,139,147,146;,
 4;139,140,148,147;,
 4;140,141,149,148;,
 4;141,142,150,149;,
 3;144,143,151;,
 3;143,145,152;,
 3;145,146,153;,
 3;146,147,154;,
 3;147,148,155;,
 3;148,149,156;,
 3;149,150,157;;
 
 MeshMaterialList {
  1;
  122;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
  Material {
   1.000000;1.000000;1.000000;1.000000;;
   0.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  78;
  0.000000;1.000000;-0.000000;,
  0.000000;0.902816;-0.430028;,
  0.336209;0.902816;-0.268118;,
  0.419246;0.902816;0.095690;,
  0.186582;0.902816;0.387441;,
  -0.186582;0.902816;0.387441;,
  -0.419245;0.902816;0.095690;,
  -0.336208;0.902816;-0.268118;,
  0.000001;0.627325;-0.778758;,
  0.608857;0.627325;-0.485547;,
  0.759232;0.627326;0.173290;,
  0.337890;0.627326;0.701636;,
  -0.337890;0.627326;0.701636;,
  -0.759232;0.627326;0.173290;,
  -0.608856;0.627326;-0.485548;,
  0.000001;0.224528;-0.974468;,
  0.761869;0.224528;-0.607571;,
  0.950036;0.224529;0.216839;,
  0.422806;0.224529;0.877965;,
  -0.422805;0.224529;0.877965;,
  -0.950035;0.224529;0.216839;,
  -0.761869;0.224528;-0.607571;,
  0.000001;-0.224528;-0.974468;,
  0.761869;-0.224529;-0.607571;,
  0.950035;-0.224529;0.216840;,
  0.422805;-0.224529;0.877965;,
  -0.422805;-0.224529;0.877965;,
  -0.950036;-0.224529;0.216839;,
  -0.761869;-0.224528;-0.607571;,
  0.000001;-0.627325;-0.778758;,
  0.608857;-0.627325;-0.485547;,
  0.759232;-0.627326;0.173290;,
  0.337890;-0.627326;0.701636;,
  -0.337890;-0.627326;0.701636;,
  -0.759232;-0.627326;0.173289;,
  -0.608856;-0.627326;-0.485548;,
  0.000000;-0.902816;-0.430028;,
  0.336209;-0.902816;-0.268118;,
  0.419246;-0.902816;0.095690;,
  0.186582;-0.902816;0.387441;,
  -0.186582;-0.902816;0.387441;,
  -0.419245;-0.902816;0.095690;,
  -0.336208;-0.902816;-0.268118;,
  0.000000;-1.000000;-0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-0.303935;-0.952693;,
  0.673656;-0.303935;-0.673655;,
  0.952693;-0.303935;-0.000000;,
  0.673656;-0.303935;0.673655;,
  0.000000;-0.303935;0.952693;,
  -0.673656;-0.303935;0.673655;,
  -0.952693;-0.303935;-0.000000;,
  -0.673656;-0.303935;-0.673655;,
  0.000000;-1.000000;-0.000000;,
  0.000000;1.000000;-0.000000;,
  0.000000;0.902816;-0.430028;,
  0.336208;0.902816;-0.268118;,
  0.419246;0.902816;0.095690;,
  0.186582;0.902816;0.387441;,
  0.608857;0.627326;-0.485547;,
  0.759232;0.627326;0.173290;,
  0.337890;0.627326;0.701636;,
  -0.337890;0.627326;0.701635;,
  0.950035;0.224529;0.216840;,
  0.422806;0.224529;0.877965;,
  0.950035;-0.224529;0.216840;,
  0.422805;-0.224529;0.877965;,
  0.000001;-0.627325;-0.778758;,
  0.608857;-0.627325;-0.485547;,
  0.759232;-0.627326;0.173290;,
  0.337890;-0.627326;0.701636;,
  -0.337890;-0.627326;0.701636;,
  0.000000;-0.902816;-0.430028;,
  0.336209;-0.902816;-0.268118;,
  0.419246;-0.902816;0.095690;,
  0.186582;-0.902816;0.387441;,
  -0.186582;-0.902816;0.387441;,
  0.000000;-1.000000;-0.000000;;
  122;
  3;0,2,1;,
  3;0,3,2;,
  3;0,4,3;,
  3;0,5,4;,
  3;0,6,5;,
  3;0,7,6;,
  3;0,1,7;,
  4;1,2,9,8;,
  4;2,3,10,9;,
  4;3,4,11,10;,
  4;4,5,12,11;,
  4;5,6,13,12;,
  4;6,7,14,13;,
  4;7,1,8,14;,
  4;8,9,16,15;,
  4;9,10,17,16;,
  4;10,11,18,17;,
  4;11,12,19,18;,
  4;12,13,20,19;,
  4;13,14,21,20;,
  4;14,8,15,21;,
  4;15,16,23,22;,
  4;16,17,24,23;,
  4;17,18,25,24;,
  4;18,19,26,25;,
  4;19,20,27,26;,
  4;20,21,28,27;,
  4;21,15,22,28;,
  4;22,23,30,29;,
  4;23,24,31,30;,
  4;24,25,32,31;,
  4;25,26,33,32;,
  4;26,27,34,33;,
  4;27,28,35,34;,
  4;28,22,29,35;,
  4;29,30,37,36;,
  4;30,31,38,37;,
  4;31,32,39,38;,
  4;32,33,40,39;,
  4;33,34,41,40;,
  4;34,35,42,41;,
  4;35,29,36,42;,
  3;36,37,43;,
  3;37,38,43;,
  3;38,39,43;,
  3;39,40,43;,
  3;40,41,43;,
  3;41,42,43;,
  3;42,36,43;,
  4;45,46,46,45;,
  4;46,47,47,46;,
  4;47,48,48,47;,
  4;48,49,49,48;,
  4;49,50,50,49;,
  4;50,51,51,50;,
  4;51,52,52,51;,
  4;52,45,45,52;,
  3;44,44,44;,
  3;44,44,44;,
  3;44,44,44;,
  3;44,44,44;,
  3;44,44,44;,
  3;44,44,44;,
  3;44,44,44;,
  3;44,44,44;,
  3;53,53,53;,
  3;53,53,53;,
  3;53,53,53;,
  3;53,53,53;,
  3;53,53,53;,
  3;53,53,53;,
  3;53,53,53;,
  3;53,53,53;,
  3;54,56,55;,
  3;54,57,56;,
  3;54,58,57;,
  3;54,5,58;,
  3;54,6,5;,
  3;54,7,6;,
  3;54,55,7;,
  4;55,56,59,8;,
  4;56,57,60,59;,
  4;57,58,61,60;,
  4;58,5,62,61;,
  4;5,6,13,62;,
  4;6,7,14,13;,
  4;7,55,8,14;,
  4;8,59,16,15;,
  4;59,60,63,16;,
  4;60,61,64,63;,
  4;61,62,19,64;,
  4;62,13,20,19;,
  4;13,14,21,20;,
  4;14,8,15,21;,
  4;15,16,23,22;,
  4;16,63,65,23;,
  4;63,64,66,65;,
  4;64,19,26,66;,
  4;19,20,27,26;,
  4;20,21,28,27;,
  4;21,15,22,28;,
  4;22,23,68,67;,
  4;23,65,69,68;,
  4;65,66,70,69;,
  4;66,26,71,70;,
  4;26,27,34,71;,
  4;27,28,35,34;,
  4;28,22,67,35;,
  4;67,68,73,72;,
  4;68,69,74,73;,
  4;69,70,75,74;,
  4;70,71,76,75;,
  4;71,34,41,76;,
  4;34,35,42,41;,
  4;35,67,72,42;,
  3;72,73,77;,
  3;73,74,77;,
  3;74,75,77;,
  3;75,76,77;,
  3;76,41,77;,
  3;41,42,77;,
  3;42,72,77;;
 }
 MeshTextureCoords {
  158;
  0.071429;0.000000;,
  0.142857;0.142857;,
  0.000000;0.142857;,
  0.214286;0.000000;,
  0.285714;0.142857;,
  0.357143;0.000000;,
  0.428571;0.142857;,
  0.500000;0.000000;,
  0.571429;0.142857;,
  0.642857;0.000000;,
  0.714286;0.142857;,
  0.785714;0.000000;,
  0.857143;0.142857;,
  0.928571;0.000000;,
  1.000000;0.142857;,
  0.142857;0.285714;,
  0.000000;0.285714;,
  0.285714;0.285714;,
  0.428571;0.285714;,
  0.571429;0.285714;,
  0.714286;0.285714;,
  0.857143;0.285714;,
  1.000000;0.285714;,
  0.142857;0.428571;,
  0.000000;0.428571;,
  0.285714;0.428571;,
  0.428571;0.428571;,
  0.571429;0.428571;,
  0.714286;0.428571;,
  0.857143;0.428571;,
  1.000000;0.428571;,
  0.142857;0.571429;,
  0.000000;0.571429;,
  0.285714;0.571429;,
  0.428571;0.571429;,
  0.571429;0.571429;,
  0.714286;0.571429;,
  0.857143;0.571429;,
  1.000000;0.571429;,
  0.142857;0.714286;,
  0.000000;0.714286;,
  0.285714;0.714286;,
  0.428571;0.714286;,
  0.571429;0.714286;,
  0.714286;0.714286;,
  0.857143;0.714286;,
  1.000000;0.714286;,
  0.142857;0.857143;,
  0.000000;0.857143;,
  0.285714;0.857143;,
  0.428571;0.857143;,
  0.571429;0.857143;,
  0.714286;0.857143;,
  0.857143;0.857143;,
  1.000000;0.857143;,
  0.071429;1.000000;,
  0.214286;1.000000;,
  0.357143;1.000000;,
  0.500000;1.000000;,
  0.642857;1.000000;,
  0.785714;1.000000;,
  0.928571;1.000000;,
  0.000000;0.000000;,
  0.125000;0.000000;,
  0.125000;1.000000;,
  0.000000;1.000000;,
  0.250000;0.000000;,
  0.250000;1.000000;,
  0.375000;0.000000;,
  0.375000;1.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.625000;0.000000;,
  0.625000;1.000000;,
  0.750000;0.000000;,
  0.750000;1.000000;,
  0.875000;0.000000;,
  0.875000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.062500;0.000000;,
  0.187500;0.000000;,
  0.312500;0.000000;,
  0.437500;0.000000;,
  0.562500;0.000000;,
  0.687500;0.000000;,
  0.812500;0.000000;,
  0.937500;0.000000;,
  0.062500;1.000000;,
  0.187500;1.000000;,
  0.312500;1.000000;,
  0.437500;1.000000;,
  0.562500;1.000000;,
  0.687500;1.000000;,
  0.812500;1.000000;,
  0.937500;1.000000;,
  0.071429;0.000000;,
  0.142857;0.142857;,
  0.000000;0.142857;,
  0.214286;0.000000;,
  0.285714;0.142857;,
  0.357143;0.000000;,
  0.428571;0.142857;,
  0.500000;0.000000;,
  0.571429;0.142857;,
  0.642857;0.000000;,
  0.714286;0.142857;,
  0.785714;0.000000;,
  0.857143;0.142857;,
  0.928571;0.000000;,
  1.000000;0.142857;,
  0.142857;0.285714;,
  0.000000;0.285714;,
  0.285714;0.285714;,
  0.428571;0.285714;,
  0.571429;0.285714;,
  0.714286;0.285714;,
  0.857143;0.285714;,
  1.000000;0.285714;,
  0.142857;0.428571;,
  0.000000;0.428571;,
  0.285714;0.428571;,
  0.428571;0.428571;,
  0.571429;0.428571;,
  0.714286;0.428571;,
  0.857143;0.428571;,
  1.000000;0.428571;,
  0.142857;0.571429;,
  0.000000;0.571429;,
  0.285714;0.571429;,
  0.428571;0.571429;,
  0.571429;0.571429;,
  0.714286;0.571429;,
  0.857143;0.571429;,
  1.000000;0.571429;,
  0.142857;0.714286;,
  0.000000;0.714286;,
  0.285714;0.714286;,
  0.428571;0.714286;,
  0.571429;0.714286;,
  0.714286;0.714286;,
  0.857143;0.714286;,
  1.000000;0.714286;,
  0.142857;0.857143;,
  0.000000;0.857143;,
  0.285714;0.857143;,
  0.428571;0.857143;,
  0.571429;0.857143;,
  0.714286;0.857143;,
  0.857143;0.857143;,
  1.000000;0.857143;,
  0.071429;1.000000;,
  0.214286;1.000000;,
  0.357143;1.000000;,
  0.500000;1.000000;,
  0.642857;1.000000;,
  0.785714;1.000000;,
  0.928571;1.000000;;
 }
}