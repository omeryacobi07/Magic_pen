// MagicPen.cpp

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// הצהרות שגרות
void AddText(char** ioppcStr);
void UpdateText(char** ioppcStr);
void DeleteText(char** ioppcStr);
void PrintText(char* ipcStr);
void SaveToFile(char* ipcStr);
void LoadFromFile(char** ioppcStr);

//-----------------------------------------------------------------------------
// Magic Pen
// ---------
//
// כללי : תוכנית המנהלת מחרוזת דינמית. המשתמש יכול להוסיף טקסט, לערוך,
//		  למחוק, להדפיס, לשמור לקובץ ולטעון אותו מקובץ.
//
// קלט : בחירות משתמש, טקסט לקליטה, פרטי עדכון ומחיקה,
//		  ושמות קבצים לשמירה או טעינה.
//
// עיבוד : בהתאם לבחירת המשתמש מתבצעת הקצאת זיכרון, שינוי מחרוזת,
//		  שינוי גודל, שמירה או טעינה.
//
// פלט : הודעות למשתמש, הדפסת המחרוזת או יצירת קבצים.
//
//-----------------------------------------------------------------------------
// מתכנת : Omer Yacobi
// מספר חניך : 330966151
// תאריך : 03/12/2025
//-----------------------------------------------------------------------------
int main()
{
	// הגדרת משתנים
	int nChoice;
	char* pcStr = NULL;

	// קטע ביצוע
	while (1)
	{
		printf("Choose an option:\n");
		printf("1. Add text to string\n");
		printf("2. Update original string\n");
		printf("3. Delete text from string\n");
		printf("4. Print string\n");
		printf("5. Save string to file\n");
		printf("6. Exit program\n");
		printf("7. Load string from file\n");

		scanf("%d", &nChoice);

		switch (nChoice)
		{
			// הוספת טקסט
		case (1):
		{
			AddText(&pcStr);

			break;
		}

		// עדכון טקסט
		case (2):
		{
			UpdateText(&pcStr);

			break;
		}

		// מחיקה מהסוף
		case (3):
		{
			DeleteText(&pcStr);

			break;
		}

		// הדפסת מחרוזת
		case (4):
		{
			PrintText(pcStr);

			break;
		}

		// שמירה לקובץ
		case (5):
		{
			SaveToFile(pcStr);

			break;
		}

		// יציאה
		case (6):
		{
			printf("Exiting program.\n");

			free(pcStr);

			return (0);
		}

		// טעינה מקובץ
		case (7):
		{
			LoadFromFile(&pcStr);

			break;
		}

		// קלט לא תקין
		default:
		{
			printf("Invalid choice. Try again.\n");

			break;
		}
		}
	}

	return (0);
}

//-----------------------------------------------------------------------------
// Add Text
// --------
//
// כללי : שגרה המקבלת אורך וטקסט מהמשתמש, מקצה זיכרון ומוסיפה את הטקסט
//		  למחרוזת הדינמית.
//
// פרמטרים :
// ioppcStr – מצביע למחרוזת (נכנס/יוצא)
//
// מחזירה : כלום.
//
//-----------------------------------------------------------------------------
void AddText(char** ioppcStr)
{
	// הגדרת משתנים
	int nLen;
	char* pcTemp;

	// קטע ביצוע
	printf("Enter length of text to add: ");
	scanf("%d", &nLen);

	pcTemp = (char*)malloc(nLen + 1);

	printf("Enter the text: ");
	scanf(" %[^\n]", pcTemp);

	pcTemp[nLen] = '\0';

	// אם זו הכנסה ראשונה
	if ((*ioppcStr) == NULL)
	{
		*ioppcStr = pcTemp;
	}
	else
	{
		// הוספה למחרוזת קיימת
		int nOldLen = strlen((*ioppcStr));

		*ioppcStr = (char*)realloc((*ioppcStr), nOldLen + nLen + 1);

		strcat((*ioppcStr), pcTemp);

		free(pcTemp);
	}
}

//-----------------------------------------------------------------------------
// Update Text
// -----------
//
// כללי : שגרה המבצעת עדכון חלקי על המחרוזת – החלפת מספר תווים החל
//		  מעמדה מסוימת, כולל שינוי גודל המחרוזת לפי הצורך.
//
// פרמטרים :
// ioppcStr – מצביע למחרוזת (נכנס/יוצא)
//
// מחזירה : כלום.
//
//-----------------------------------------------------------------------------
void UpdateText(char** ioppcStr)
{
	// הגדרת משתנים
	int nPos;
	int nNumChars;
	int nOldLen;
	int nUpdateLen;
	char arrcUpdate[256];
	char* pcRight;

	// קטע ביצוע
	if ((*ioppcStr) == NULL)
	{
		printf("String is empty.\n");

		return;
	}

	nOldLen = strlen((*ioppcStr));

	printf("Enter position to edit (0 to %d): ", nOldLen - 1);
	scanf("%d", &nPos);

	if ((nPos < 0) || (nPos > nOldLen))
	{
		printf("Out of bounds.\n");

		return;
	}

	printf("Enter number of characters to update: ");
	scanf("%d", &nNumChars);

	printf("Enter the updated text: ");
	scanf(" %[^\n]", arrcUpdate);

	nUpdateLen = strlen(arrcUpdate);

	// שמירת הצד הימני
	pcRight = (char*)malloc(nOldLen - nPos - nNumChars + 1);

	int nR = 0;
	for (int nI = nPos + nNumChars; nI < nOldLen; ++nI, ++nR)
	{
		pcRight[nR] = (*ioppcStr)[nI];
	}
	pcRight[nR] = '\0';

	// שינוי גודל המחרוזת
	*ioppcStr = (char*)realloc((*ioppcStr),
		nPos + nUpdateLen + strlen(pcRight) + 1);

	// הכנסת הטקסט החדש
	for (int nI = 0; nI < nUpdateLen; ++nI)
	{
		(*ioppcStr)[nPos + nI] = arrcUpdate[nI];
	}

	// החזרת החלק הימני
	for (int nI = 0; pcRight[nI] != '\0'; ++nI)
	{
		(*ioppcStr)[nPos + nUpdateLen + nI] = pcRight[nI];
	}

	(*ioppcStr)[nPos + nUpdateLen + strlen(pcRight)] = '\0';

	free(pcRight);
}

//-----------------------------------------------------------------------------
// Delete Text
// -----------
//
// כללי : שגרה המוחקת מספר תווים מסוף המחרוזת ומשנה את גודל ההקצאה.
//
// פרמטרים :
// ioppcStr – מצביע למחרוזת (נכנס/יוצא)
//
// מחזירה : כלום.
//
//-----------------------------------------------------------------------------
void DeleteText(char** ioppcStr)
{
	// הגדרת משתנים
	int nNum;
	int nOldLen;

	// קטע ביצוע
	if ((*ioppcStr) == NULL)
	{
		printf("String is empty.\n");

		return;
	}

	printf("Enter number of characters to delete: ");
	scanf("%d", &nNum);

	nOldLen = strlen((*ioppcStr));

	// מחיקת כל המחרוזת
	if (nNum >= nOldLen)
	{
		free(*ioppcStr);

		*ioppcStr = NULL;
	}
	else
	{
		(*ioppcStr)[nOldLen - nNum] = '\0';

		*ioppcStr = (char*)realloc((*ioppcStr), nOldLen - nNum + 1);
	}
}

//-----------------------------------------------------------------------------
// Print Text
// ----------
//
// כללי : שגרה המדפיסה את המחרוזת הדינמית.
//
// פרמטרים :
// ipcStr – מצביע למחרוזת (קלט)
//
// מחזירה : כלום.
//
//-----------------------------------------------------------------------------
void PrintText(char* ipcStr)
{
	// קטע ביצוע
	if (ipcStr == NULL)
	{
		printf("String is empty.\n");
	}
	else
	{
		printf("Current string: %s\n", ipcStr);
	}
}

//-----------------------------------------------------------------------------
// Save To File
// ------------
//
// כללי : שגרה השומרת את המחרוזת לקובץ טקסט.
//
// פרמטרים :
// ipcStr – מחרוזת לשמירה (קלט)
//
// מחזירה : כלום.
//
//-----------------------------------------------------------------------------
void SaveToFile(char* ipcStr)
{
	// הגדרת משתנים
	char arrcFile[100];
	FILE* pfsFile;

	// קטע ביצוע
	if (ipcStr == NULL)
	{
		printf("String is empty.\n");

		return;
	}

	printf("Enter filename: ");
	scanf("%s", arrcFile);

	pfsFile = fopen(arrcFile, "wt");

	if (pfsFile == NULL)
	{
		printf("Error opening file.\n");

		return;
	}

	fprintf(pfsFile, "%s", ipcStr);

	fclose(pfsFile);

	printf("String saved to %s\n", arrcFile);
}

//-----------------------------------------------------------------------------
// Load From File
// --------------
//
// כללי : שגרה הטוענת מחרוזת מקובץ ומקצה לה זיכרון לפי הגודל.
//
// פרמטרים :
// ioppcStr – מצביע למחרוזת (נכנס/יוצא)
//
// מחזירה : כלום.
//
//-----------------------------------------------------------------------------
void LoadFromFile(char** ioppcStr)
{
	// הגדרת משתנים
	char arrcFile[100];
	FILE* pfsFile;
	long nSize;
	char* pcTemp;

	// קטע ביצוע
	printf("Enter filename to load: ");
	scanf("%s", arrcFile);

	pfsFile = fopen(arrcFile, "rt");

	if (pfsFile == NULL)
	{
		printf("Error opening file.\n");

		return;
	}

	fseek(pfsFile, 0, SEEK_END);
	nSize = ftell(pfsFile);
	fseek(pfsFile, 0, SEEK_SET);

	pcTemp = (char*)malloc(nSize + 1);

	fread(pcTemp, 1, nSize, pfsFile);
	pcTemp[nSize] = '\0';

	fclose(pfsFile);

	free(*ioppcStr);

	*ioppcStr = pcTemp;

	printf("String loaded from %s\n", arrcFile);
}