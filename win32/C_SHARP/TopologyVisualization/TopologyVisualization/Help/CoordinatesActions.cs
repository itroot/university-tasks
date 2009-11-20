using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using Microsoft.DirectX;

namespace TopologyVisualization.Help
{
    class CoordinatesActions
    {
        public static string CubantRecord2Code(string record)
        {
            string code = "";
            if (record[0] == '/' && record[record.Length - 1] == '/')
                record = record.Substring(1, record.Length - 2);
            else
                throw new Exception();
            for (int i = 0; i < record.Length; i += 2)
            {
                if (i == record.Length - 1)
                    code += record[i];
                else
                    if (record[i + 1] == ',')
                        code += record[i];
            }
            return code;
        }

        public static int[] add(int []coord1,int[] coord2)
        { 
            if (coord1.Length!=coord2.Length)
                throw new Exception("Размерность векторов координат не совпадает. Сложение не возможно.");
            int[] res = new int[coord1.Length];
            for (int i = 0; i < coord1.Length; i++)
                res[i] = coord1[i] + coord2[i];
            return res;
        }

        public static float[] add(float[] coord1, float[] coord2)
        {
            if (coord1.Length != coord2.Length)
                throw new Exception("Размерность векторов координат не совпадает. Сложение не возможно.");
            float[] res = new float[coord1.Length];
            for (int i = 0; i < coord1.Length; i++)
                res[i] = coord1[i] + coord2[i];
            return res;
        }

        public static int[] multiply(int[] coord, int koef)
        {
            int[] res = new int[coord.Length];
            for (int i = 0; i < coord.Length; i++)
                res[i] = coord[i]*koef;
            return res;
        }

        public static float[] multiply(float[] coord, float koef)
        {
            float[] res = new float[coord.Length];
            for (int i = 0; i < coord.Length; i++)
                res[i] = coord[i] * koef;
            return res;
        }

        public static bool equals(int[] coord1,int[] coord2)
        {
            if (coord1.Length != coord2.Length)
                throw new Exception("Размерность векторов координат не совпадает. Сравнение не возможно.");
            for (int i = 0; i < coord1.Length; i++)
                if (coord1[i] != coord2[i])
                    return false;
            return true;
        }

        public static bool equals(float[] coord1, float[] coord2)
        {
            if (coord1.Length != coord2.Length)
                throw new Exception("Размерность векторов координат не совпадает. Сравнение не возможно.");
            for (int i = 0; i < coord1.Length; i++)
                if (coord1[i] != coord2[i])
                    return false;
            return true;
        }

        public static int[] getNullIntCoord(int dimm)
        {
            int[] coord = new int[dimm];
            for (int i = 0; i < dimm; i++)
                coord[i] = 0;
            return coord;
        }

        public static float[] getNullFloatCoord(int dimm)
        {
            float[] coord = new float[dimm];
            for (int i = 0; i < dimm; i++)
                coord[i] = 0.0f;
            return coord;
        }

        public static bool consist(int[] point, int[] code)
        {
            if (point.Length != code.Length)
                throw new Exception("Размерность векторов координат не совпадает. Сравнение на вложенность не возможно.");
            for (int i = 0; i < point.Length; i++)
                if ((code[i] != 2) && (code[i] != point[i]))
                    return false;
            return true;
        }

        public static bool consist(int[] point, string code)
        {
            if (point.Length != code.Length)
                throw new Exception("Размерность векторов координат не совпадает. Сравнение на вложенность не возможно.");
            int[] Code = new int[code.Length];
            for (int i = 0; i < code.Length; i++)
                Code[i] = code[i] - '0';
            return consist(point, Code);
        }

        public static int[] peresechenie(int[] coord1, int[] coord2)
        {
            if (coord1.Length!=coord2.Length)
                throw new Exception("Размерность не совпадает. Невозможно найти пересечение.");
            int[] res = new int[coord1.Length];
            for (int i = 0; i < coord1.Length; i++)
                if (coord1[i] == 2)
                    res[i] = coord2[i];
                else
                    if ((coord1[i] == 1 && coord2[i] == 0) || (coord1[i] == 0 && coord2[i] == 1))
                        return null;
                    else
                        res[i] = coord1[i];
            return res;
        }

        public static bool isSquare(int[] code) 
        {
            int counter = 0;
            for (int i = 0; i < code.Length; i++)
                if (code[i] == 2)
                    counter++;
            return counter == 2;
        }

        public static int[] getCode(string s)
        {
            int[] res = new int[s.Length];
            for (int i = 0; i < s.Length; i++)
                res[i] = s[i] - '0';
            return res;
        }

        public static string getString(int[] s)
        {
            string res = "";
            for (int i = 0; i < s.Length; i++)
                res += (char)('0' + s[i]);
            return res;
        }

        public static LinkedList<int[]> getAllSquares(int[] code)
        {
            LinkedList<int> two = new LinkedList<int>(); ;
            for (int i = 0; i < code.Length; i++)
                if (code[i] == 2)
                    two.AddLast(i);
            if (two.Count < 2)
                throw new Exception("Нет квадратов в коде"+getString(code));
            if (two.Count == 2)
            {
                LinkedList<int[]> res = new LinkedList<int[]>();
                res.AddLast(code);
                return res;
            }
            else 
            {
                LinkedList<int[]> res = new LinkedList<int[]>();
                int[] twos = two.ToArray();
                int[][] allCodes = getAllPoints(twos.Length - 2);
                for (int i = 0; i < twos.Length; i++)
                    for (int j = i + 1; j < twos.Length; j++)
                    {
                        int[] resultcode = new int[code.Length];
                        for (int k = 0; k < code.Length; k++)
                        {
                            resultcode[k] = code[k];
                        }
                        for (int l = 0; l < allCodes.Length; l++)
                        {
                            int counter = 0;
                            for (int m = 0; m < twos.Length; m++)
                            {
                                if (m != i && m != j)
                                    resultcode[twos[m]] = allCodes[l][counter++];
                                else
                                    resultcode[twos[m]] = 2;
                            }
                            int[] tmp = new int[resultcode.Length];
                            for (int x = 0; x < resultcode.Length; x++)
                                tmp[x] = resultcode[x];
                            res.AddLast(tmp);
                        }
                    }
                return res;
            }
        }

        public static int[] addOne(int[] code)
        {
            for (int i = code.Length - 1; i >= 0; i--)
            {
                if (code[i] == 0)
                {
                    code[i] = 1;
                    return code;
                }
                else
                {
                    code[i] = 0;
                }
            }
            throw new Exception("Переполнение при увеличении кода на единицу.");
        }

        public static int[][] getAllPoints(int dim)
        {
            int length = 1;
            for (int i = 0; i < dim; i++)
                length *= 2;
            int[] res = new int[dim];
            int[][] result = new int[length][];
            result[0] = new int[dim];
            for (int i = 0; i < dim; i++)
            {
                res[i] = 0;
                result[0][i] = 0;
            }
            
            int counter=1;
            while (true)
            {
                try
                {
                    res = addOne(res);
                    result[counter] = new int[res.Length];
                    for (int i = 0; i < res.Length; i++)
                    {
                        result[counter][i] = res[i];
                    }
                    counter++;
                }
                catch (Exception)
                {
                    break;
                }
            }
            return result;
        }

        public static Vector3 getVector(float[] coords,Vector3[] Basis)
        {
            Vector3 result = new Vector3(0.0f,0.0f,0.0f);
            for (int i = 0; i < coords.Length; i++)
                result += coords[i] * Basis[i];
            return result;
        }

        public static Vector3 getVector(int[] coords, Vector3[] Basis)
        {
            Vector3 result = new Vector3(0.0f, 0.0f, 0.0f);
            for (int i = 0; i < coords.Length; i++)
                result += coords[i] * Basis[i];
            return result;
        }

        public static bool consist(string[] codes, int[] point)
        {
            for(int i=0;i<codes.Length;i++)
                if (consist(point,codes[i]))
                    return true;
            return false;
        }

        public static bool consist(string[] codes, int[] point1,int[] point2)
        {
            for (int i = 0; i < codes.Length; i++)
                if (consist(point1, codes[i]) && consist(point2,codes[i]))
                    return true;
            return false;
        }
    }
}
