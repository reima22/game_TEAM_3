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
 90;
 -1.36769;-0.12401;-1.77660;,
 -0.79454;-0.13658;-2.12124;,
 -1.02957;-16.44461;-2.01516;,
 -1.60271;-16.43203;-1.67051;,
 -0.14752;-0.14906;-2.29043;,
 -0.38254;-16.45709;-2.18434;,
 0.52099;-0.16042;-2.27045;,
 0.28596;-16.46846;-2.16436;,
 1.15680;-0.16977;-2.06291;,
 0.92177;-16.47780;-1.95682;,
 1.70842;-0.17635;-1.68465;,
 1.47339;-16.48437;-1.57856;,
 2.13115;-0.17960;-1.16630;,
 1.89612;-16.48762;-1.06020;,
 2.39074;-0.17926;-0.54985;,
 2.15572;-16.48731;-0.44376;,
 2.46618;-0.17542;0.11475;,
 2.23115;-16.48345;0.22085;,
 2.35134;-0.16831;0.77367;,
 2.11631;-16.47634;0.87975;,
 2.05553;-0.15849;1.37351;,
 1.82050;-16.46655;1.47960;,
 1.60271;-0.14690;1.86569;,
 1.36768;-16.45492;1.97179;,
 1.02957;-0.13431;2.21034;,
 0.79454;-16.44235;2.31642;,
 0.38254;-0.12183;2.37952;,
 0.14751;-16.42987;2.48561;,
 -0.28596;-0.11045;2.35955;,
 -0.52099;-16.41850;2.46564;,
 -0.92178;-0.10113;2.15200;,
 -1.15680;-16.40915;2.25808;,
 -1.47340;-0.09456;1.77374;,
 -1.70842;-16.40258;1.87983;,
 -1.89613;-0.09130;1.25539;,
 -2.13115;-16.39934;1.36148;,
 -2.15572;-0.09161;0.63894;,
 -2.39075;-16.39966;0.74503;,
 -2.23115;-0.09547;-0.02566;,
 -2.46619;-16.40352;0.08044;,
 -2.11632;-0.10260;-0.68457;,
 -2.35134;-16.41065;-0.57849;,
 -1.82050;-0.11238;-1.28442;,
 -2.05553;-16.42041;-1.17834;,
 -1.36769;-0.12401;-1.77660;,
 -1.60271;-16.43203;-1.67051;,
 0.11751;-0.13545;0.04454;,
 0.11751;-0.13545;0.04454;,
 0.11751;-0.13545;0.04454;,
 0.11751;-0.13545;0.04454;,
 0.11751;-0.13545;0.04454;,
 0.11751;-0.13545;0.04454;,
 0.11751;-0.13545;0.04454;,
 0.11751;-0.13545;0.04454;,
 0.11751;-0.13545;0.04454;,
 0.11751;-0.13545;0.04454;,
 0.11751;-0.13545;0.04454;,
 0.11751;-0.13545;0.04454;,
 0.11751;-0.13545;0.04454;,
 0.11751;-0.13545;0.04454;,
 0.11751;-0.13545;0.04454;,
 0.11751;-0.13545;0.04454;,
 0.11751;-0.13545;0.04454;,
 0.11751;-0.13545;0.04454;,
 0.11751;-0.13545;0.04454;,
 0.11751;-0.13545;0.04454;,
 0.11751;-0.13545;0.04454;,
 0.11751;-0.13545;0.04454;,
 -0.11752;-16.44347;0.15063;,
 -0.11752;-16.44347;0.15063;,
 -0.11752;-16.44347;0.15063;,
 -0.11752;-16.44347;0.15063;,
 -0.11752;-16.44347;0.15063;,
 -0.11752;-16.44347;0.15063;,
 -0.11752;-16.44347;0.15063;,
 -0.11752;-16.44347;0.15063;,
 -0.11752;-16.44347;0.15063;,
 -0.11752;-16.44347;0.15063;,
 -0.11752;-16.44347;0.15063;,
 -0.11752;-16.44347;0.15063;,
 -0.11752;-16.44347;0.15063;,
 -0.11752;-16.44347;0.15063;,
 -0.11752;-16.44347;0.15063;,
 -0.11752;-16.44347;0.15063;,
 -0.11752;-16.44347;0.15063;,
 -0.11752;-16.44347;0.15063;,
 -0.11752;-16.44347;0.15063;,
 -0.11752;-16.44347;0.15063;,
 -0.11752;-16.44347;0.15063;,
 -0.11752;-16.44347;0.15063;;
 
 66;
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
 3;46,1,0;,
 3;47,4,1;,
 3;48,6,4;,
 3;49,8,6;,
 3;50,10,8;,
 3;51,12,10;,
 3;52,14,12;,
 3;53,16,14;,
 3;54,18,16;,
 3;55,20,18;,
 3;56,22,20;,
 3;57,24,22;,
 3;58,26,24;,
 3;59,28,26;,
 3;60,30,28;,
 3;61,32,30;,
 3;62,34,32;,
 3;63,36,34;,
 3;64,38,36;,
 3;65,40,38;,
 3;66,42,40;,
 3;67,44,42;,
 3;68,3,2;,
 3;69,2,5;,
 3;70,5,7;,
 3;71,7,9;,
 3;72,9,11;,
 3;73,11,13;,
 3;74,13,15;,
 3;75,15,17;,
 3;76,17,19;,
 3;77,19,21;,
 3;78,21,23;,
 3;79,23,25;,
 3;80,25,27;,
 3;81,27,29;,
 3;82,29,31;,
 3;83,31,33;,
 3;84,33,35;,
 3;85,35,37;,
 3;86,37,39;,
 3;87,39,41;,
 3;88,41,43;,
 3;89,43,45;;
 
 MeshMaterialList {
  1;
  66;
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
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "\\data\\TEXTURE\\cloth_01.jpg";
   }
  }
 }
 MeshTextureCoords {
  90;
  0.000000;0.000000;,
  0.045450;0.000000;,
  0.045450;1.000000;,
  0.000000;1.000000;,
  0.090910;0.000000;,
  0.090910;1.000000;,
  0.136360;0.000000;,
  0.136360;1.000000;,
  0.181820;0.000000;,
  0.181820;1.000000;,
  0.227270;0.000000;,
  0.227270;1.000000;,
  0.272730;0.000000;,
  0.272730;1.000000;,
  0.318180;0.000000;,
  0.318180;1.000000;,
  0.363640;0.000000;,
  0.363640;1.000000;,
  0.409090;0.000000;,
  0.409090;1.000000;,
  0.454550;0.000000;,
  0.454550;1.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.545450;0.000000;,
  0.545450;1.000000;,
  0.590910;0.000000;,
  0.590910;1.000000;,
  0.636360;0.000000;,
  0.636360;1.000000;,
  0.681820;0.000000;,
  0.681820;1.000000;,
  0.727270;0.000000;,
  0.727270;1.000000;,
  0.772730;0.000000;,
  0.772730;1.000000;,
  0.818180;0.000000;,
  0.818180;1.000000;,
  0.863640;0.000000;,
  0.863640;1.000000;,
  0.909090;0.000000;,
  0.909090;1.000000;,
  0.954550;0.000000;,
  0.954550;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.022730;0.000000;,
  0.068180;0.000000;,
  0.113640;0.000000;,
  0.159090;0.000000;,
  0.204550;0.000000;,
  0.250000;0.000000;,
  0.295450;0.000000;,
  0.340910;0.000000;,
  0.386360;0.000000;,
  0.431820;0.000000;,
  0.477270;0.000000;,
  0.522730;0.000000;,
  0.568180;0.000000;,
  0.613640;0.000000;,
  0.659090;0.000000;,
  0.704550;0.000000;,
  0.750000;0.000000;,
  0.795450;0.000000;,
  0.840910;0.000000;,
  0.886360;0.000000;,
  0.931820;0.000000;,
  0.977270;0.000000;,
  0.022730;1.000000;,
  0.068180;1.000000;,
  0.113640;1.000000;,
  0.159090;1.000000;,
  0.204550;1.000000;,
  0.250000;1.000000;,
  0.295450;1.000000;,
  0.340910;1.000000;,
  0.386360;1.000000;,
  0.431820;1.000000;,
  0.477270;1.000000;,
  0.522730;1.000000;,
  0.568180;1.000000;,
  0.613640;1.000000;,
  0.659090;1.000000;,
  0.704550;1.000000;,
  0.750000;1.000000;,
  0.795450;1.000000;,
  0.840910;1.000000;,
  0.886360;1.000000;,
  0.931820;1.000000;,
  0.977270;1.000000;;
 }
 MeshVertexColors {
  90;
  0;1.000000;1.000000;1.000000;1.000000;,
  1;1.000000;1.000000;1.000000;1.000000;,
  2;1.000000;1.000000;1.000000;1.000000;,
  3;1.000000;1.000000;1.000000;1.000000;,
  4;1.000000;1.000000;1.000000;1.000000;,
  5;1.000000;1.000000;1.000000;1.000000;,
  6;1.000000;1.000000;1.000000;1.000000;,
  7;1.000000;1.000000;1.000000;1.000000;,
  8;1.000000;1.000000;1.000000;1.000000;,
  9;1.000000;1.000000;1.000000;1.000000;,
  10;1.000000;1.000000;1.000000;1.000000;,
  11;1.000000;1.000000;1.000000;1.000000;,
  12;1.000000;1.000000;1.000000;1.000000;,
  13;1.000000;1.000000;1.000000;1.000000;,
  14;1.000000;1.000000;1.000000;1.000000;,
  15;1.000000;1.000000;1.000000;1.000000;,
  16;1.000000;1.000000;1.000000;1.000000;,
  17;1.000000;1.000000;1.000000;1.000000;,
  18;1.000000;1.000000;1.000000;1.000000;,
  19;1.000000;1.000000;1.000000;1.000000;,
  20;1.000000;1.000000;1.000000;1.000000;,
  21;1.000000;1.000000;1.000000;1.000000;,
  22;1.000000;1.000000;1.000000;1.000000;,
  23;1.000000;1.000000;1.000000;1.000000;,
  24;1.000000;1.000000;1.000000;1.000000;,
  25;1.000000;1.000000;1.000000;1.000000;,
  26;1.000000;1.000000;1.000000;1.000000;,
  27;1.000000;1.000000;1.000000;1.000000;,
  28;1.000000;1.000000;1.000000;1.000000;,
  29;1.000000;1.000000;1.000000;1.000000;,
  30;1.000000;1.000000;1.000000;1.000000;,
  31;1.000000;1.000000;1.000000;1.000000;,
  32;1.000000;1.000000;1.000000;1.000000;,
  33;1.000000;1.000000;1.000000;1.000000;,
  34;1.000000;1.000000;1.000000;1.000000;,
  35;1.000000;1.000000;1.000000;1.000000;,
  36;1.000000;1.000000;1.000000;1.000000;,
  37;1.000000;1.000000;1.000000;1.000000;,
  38;1.000000;1.000000;1.000000;1.000000;,
  39;1.000000;1.000000;1.000000;1.000000;,
  40;1.000000;1.000000;1.000000;1.000000;,
  41;1.000000;1.000000;1.000000;1.000000;,
  42;1.000000;1.000000;1.000000;1.000000;,
  43;1.000000;1.000000;1.000000;1.000000;,
  44;1.000000;1.000000;1.000000;1.000000;,
  45;1.000000;1.000000;1.000000;1.000000;,
  46;1.000000;1.000000;1.000000;1.000000;,
  47;1.000000;1.000000;1.000000;1.000000;,
  48;1.000000;1.000000;1.000000;1.000000;,
  49;1.000000;1.000000;1.000000;1.000000;,
  50;1.000000;1.000000;1.000000;1.000000;,
  51;1.000000;1.000000;1.000000;1.000000;,
  52;1.000000;1.000000;1.000000;1.000000;,
  53;1.000000;1.000000;1.000000;1.000000;,
  54;1.000000;1.000000;1.000000;1.000000;,
  55;1.000000;1.000000;1.000000;1.000000;,
  56;1.000000;1.000000;1.000000;1.000000;,
  57;1.000000;1.000000;1.000000;1.000000;,
  58;1.000000;1.000000;1.000000;1.000000;,
  59;1.000000;1.000000;1.000000;1.000000;,
  60;1.000000;1.000000;1.000000;1.000000;,
  61;1.000000;1.000000;1.000000;1.000000;,
  62;1.000000;1.000000;1.000000;1.000000;,
  63;1.000000;1.000000;1.000000;1.000000;,
  64;1.000000;1.000000;1.000000;1.000000;,
  65;1.000000;1.000000;1.000000;1.000000;,
  66;1.000000;1.000000;1.000000;1.000000;,
  67;1.000000;1.000000;1.000000;1.000000;,
  68;1.000000;1.000000;1.000000;1.000000;,
  69;1.000000;1.000000;1.000000;1.000000;,
  70;1.000000;1.000000;1.000000;1.000000;,
  71;1.000000;1.000000;1.000000;1.000000;,
  72;1.000000;1.000000;1.000000;1.000000;,
  73;1.000000;1.000000;1.000000;1.000000;,
  74;1.000000;1.000000;1.000000;1.000000;,
  75;1.000000;1.000000;1.000000;1.000000;,
  76;1.000000;1.000000;1.000000;1.000000;,
  77;1.000000;1.000000;1.000000;1.000000;,
  78;1.000000;1.000000;1.000000;1.000000;,
  79;1.000000;1.000000;1.000000;1.000000;,
  80;1.000000;1.000000;1.000000;1.000000;,
  81;1.000000;1.000000;1.000000;1.000000;,
  82;1.000000;1.000000;1.000000;1.000000;,
  83;1.000000;1.000000;1.000000;1.000000;,
  84;1.000000;1.000000;1.000000;1.000000;,
  85;1.000000;1.000000;1.000000;1.000000;,
  86;1.000000;1.000000;1.000000;1.000000;,
  87;1.000000;1.000000;1.000000;1.000000;,
  88;1.000000;1.000000;1.000000;1.000000;,
  89;1.000000;1.000000;1.000000;1.000000;;
 }
}
