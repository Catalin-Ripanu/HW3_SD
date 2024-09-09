#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
/*Definirea unor macro-uri utile*/
#define MAX1 200
#define MAX2 10
#define MAX3 20
#define MAX 10000
#define MAX4 9999
/*Structura ce reprezinta o lista dublu inlantuita*/
typedef struct List_Struct
{
  /*Numarul de noduri */
  int Number_of_nodes;
  /*Mutare spre un alt nod(inainte) */
  struct List_Struct *Next;
  /*Obiect generic util pentru ceea ce urmeaza */
  void *Object;
  /*Sfarsitul listei */
  struct List_Struct *Tail;
  /*O functie ce compara numele actorilor */
  int (*Actor_Compare) (const void *, const void *);
  /*Mutare spre un alt nod(inapoi) */
  struct List_Struct *Prev;
} List;
/*Structura ce reprezinta o lista (Sentinel)*/
typedef struct List2_Struct
{				/*Inceputul listei */
  List *Head;
  /*Camp pentru a stoca numele unui actor */
  char *Name_Actor;
} List2;
/*Structura ce reprezinta proprietatile unui actor*/
typedef struct Actor_Struct
{				/*Codul asociat unui actor */
  int Actor_Code;
  /*Numele unui actor */
  char *Actor_Name;
} Actor;
/*Structura ce reprezinta o coada*/
typedef struct Queue_Struct
{				/*Numarul de noduri */
  int Number_of_nodes;
  /*Sfarsitul cozii */
  List *Tail;
  /*Inceputul cozii */
  List *Head;
} Queue;
/*Structura ce reprezinta un arbore binar*/
typedef struct BinaryTree_Struct
{				/*Numarul de noduri */
  int Number_of_nodes;
  /*Obiect generic util pentru ceea ce urmeaza */
  void *Object;
  /*Fiul stang al unui nod */
  struct BinaryTree_Struct *Left_Son;
  /*Fiul drept al unui nod */
  struct BinaryTree_Struct *Right_Son;
  /*Parintele unui nod */
  struct BinaryTree_Struct *Father;
  /*O functie ce compara numele actorilor */
  int (*Actor_Compare) (const void *, const void *);
} BinaryTree;
/*O structura ce reprezinta graful actorilor*/
typedef struct Actor_Graph_Struct
{
  /*Numarul de noduri */
  int Number_of_nodes;
  /*Distanta unui nod fata de alt nod */
  int *Distance;
  /*Graful este reprezentat cu liste de adiacenta */
  List2 **Adjency_List;
} Graph;
/*Scrierea actorilor in fisier */
void Print_Actors (BinaryTree *, FILE *);
/*Alocarea dinamica a memoriei dupa obtinerea unui sir*/
char *Duplicate (char *);
/*Compararea a doua numere*/
int
Compare_Numbers (const void *x, const void *y)
{
  return *(int *) x - *(int *) y;
}

/*Minimul*/
int
min (int a, int b)
{
  if (a > b)
    return b;
  return a;
}

/*Initializarea unei liste dublu inlantuite*/
List *
Get_List (void *Object, int (*Actor_Compare) (const void *, const void *))
{
  List *Adjency_List = (List *) malloc (sizeof (List));
  Adjency_List->Number_of_nodes = 1;
  Adjency_List->Object = Object;
  Adjency_List->Next = NULL;
  Adjency_List->Actor_Compare = Actor_Compare;
  Adjency_List->Tail = Adjency_List;
  Adjency_List->Prev = NULL;
  /*Returnarea listei modificate */
  return Adjency_List;
}

/*Adaugarea unui nod intr-o lista*/
List *
Push_List (List * Adjency_List, void *Object,
	   int (*Actor_Compare) (const void *, const void *))
{
  /*Daca lista este vida */
  if (Adjency_List == NULL)
    return Get_List (Object, Actor_Compare);
  List *Actor_New = Get_List (Object, Actor_Compare);
  Adjency_List->Tail->Next = Actor_New;
  Actor_New->Prev = Adjency_List->Tail;
  Adjency_List->Tail = Actor_New;
  Adjency_List->Number_of_nodes++;
  /*Returnarea listei modificate */
  return Adjency_List;
}

/*Initializarea unui actor*/
Actor *
Get_Actor (char *Name)
{
  Actor *Actor_New = (Actor *) malloc (sizeof (Actor));
  Actor_New->Actor_Name = Duplicate (Name);
  return Actor_New;
}

/*Distrugerea unui actor(eliberarea memoriei)*/
Actor *
Destroy_Actor (Actor * Actor)
{
  free (Actor->Actor_Name);
  free (Actor);
  return NULL;
}

/*Alocarea memoriei pentru un numar*/
int *
Integer (int Number)
{
  int *rez = (int *) malloc (sizeof (int));
  *rez = Number;
  return rez;
}

/*Distrugerea unei liste (eliberarea memoriei)*/
List *
Destroy_List (List * Adjency_List)
{
  while (Adjency_List)
    {
      List *toDelete = Adjency_List;
      Adjency_List = Adjency_List->Next;
      free (toDelete->Object);
      free (toDelete);
    }
  return NULL;
}

/*Initializarea unui arbore binar*/
BinaryTree *
Get_BinaryTree (void *Object,
		int (*Actor_Compare) (const void *, const void *),
		BinaryTree * parent)
{
  BinaryTree *Binary_Actor = (BinaryTree *) malloc (sizeof (BinaryTree));
  Binary_Actor->Actor_Compare = Actor_Compare;
  Binary_Actor->Number_of_nodes = 1;
  Binary_Actor->Left_Son = NULL;
  Binary_Actor->Right_Son = NULL;
  Binary_Actor->Object = Object;
  Binary_Actor->Father = parent;
/*Returnarea arborelui modificat*/
  return Binary_Actor;
}

/*Adaugarea unui nod in arbore*/
BinaryTree *
Push_BinaryTree (BinaryTree * Binary_Actor, void *Object,
		 int (*Actor_Compare) (const void *, const void *))
{
  /*Daca arborele este vid */
  if (Binary_Actor == NULL)
    return Get_BinaryTree (Object, Actor_Compare, NULL);
  /*Compararea actorilor */
  if (Binary_Actor->Actor_Compare (Binary_Actor->Object, Object) > 0)
    {
      /*Daca fiul stang este vid */
      if (Binary_Actor->Left_Son == NULL)
	{			/*Este adaugat */
	  Binary_Actor->Left_Son =
	    Get_BinaryTree (Object, Actor_Compare, Binary_Actor);
	  BinaryTree *Contor;
	  /*Marirea numarului de noduri */
	  for (Contor = Binary_Actor; Contor != NULL; Contor = Contor->Father)
	    Contor->Number_of_nodes = Contor->Number_of_nodes + 1;
/*Returnarea arborelui modificat*/
	  return Binary_Actor;
	}
      else
	{
	  /*Daca fiul stang nu este vid */
	  /*Merg spre stanga */
	  Binary_Actor->Left_Son =
	    Push_BinaryTree (Binary_Actor->Left_Son, Object, Actor_Compare);
	  /*Returnarea arborelui modificat */
	  return Binary_Actor;
	}
    }
  else if (Binary_Actor->Actor_Compare (Binary_Actor->Object, Object) < 0)
    {				/*Daca fiul drept este vid */
      if (Binary_Actor->Right_Son == NULL)
	{
	  /*Este adaugat */
	  Binary_Actor->Right_Son =
	    Get_BinaryTree (Object, Actor_Compare, Binary_Actor);
	  BinaryTree *Contor;
	  /*Marirea numarului de noduri */
	  for (Contor = Binary_Actor; Contor != NULL; Contor = Contor->Father)
	    Contor->Number_of_nodes = Contor->Number_of_nodes + 1;
	  /*Returnarea arborelui modificat */
	  return Binary_Actor;
	}
      else
	{
	  /*Daca fiul drept nu este vid */
	  /*Merg spre dreapta */
	  Binary_Actor->Right_Son =
	    Push_BinaryTree (Binary_Actor->Right_Son, Object, Actor_Compare);
	  /*Returnarea arborelui modificat */
	  return Binary_Actor;
	}
    }
/*Returnarea arborelui modificat*/
  return Binary_Actor;
}

/*Compararea unor nume*/
int
Compare_Names (const void *x, const void *y)
{
  Actor *A = (Actor *) x;
  Actor *B = (Actor *) y;

  return strcmp (A->Actor_Name, B->Actor_Name);
}

/*Verificarea existentei unui actor in arbore*/
void *
Verify_BinaryTree (BinaryTree * Binary_Actor, void *Object)
{				/*Daca arborele este vid */
  if (Binary_Actor == NULL)
    return NULL;
/*Daca se gaseste actorul cautat*/
  if (Binary_Actor->Actor_Compare (Binary_Actor->Object, Object) == 0)
    /*Il returnez */
    return Binary_Actor->Object;
/*Cautarea unui actor mergand spre stanga*/
  if (Binary_Actor->Actor_Compare (Binary_Actor->Object, Object) > 0)
    return Verify_BinaryTree (Binary_Actor->Left_Son, Object);
/*Cautarea unui actor mergand spre dreapta*/
  return Verify_BinaryTree (Binary_Actor->Right_Son, Object);
}

/*Distrugerea unui arbore binar(eliberarea memoriei)*/
BinaryTree *
Destroy_BinaryTree (BinaryTree * Binary_Actor)
{
  if (!Binary_Actor)
    return NULL;
  Destroy_BinaryTree (Binary_Actor->Left_Son);
  Destroy_BinaryTree (Binary_Actor->Right_Son);
  Actor *Free_Actor = (Actor *) Binary_Actor->Object;
  Free_Actor = Destroy_Actor (Free_Actor);
  free (Binary_Actor);
  return NULL;
}

/*Initializarea unei cozi*/
Queue *
Get_Queue (void *Object, int (*Actor_Compare) (const void *, const void *))
{
  Queue *Queue1 = (Queue *) malloc (sizeof (Queue));

  Queue1->Number_of_nodes = 1;
  /*Coada este o lista */
  Queue1->Head = Queue1->Tail = Get_List (Object, Actor_Compare);
  /*Returnarea cozii modificate */
  return Queue1;
}

/*Verificarea continutului unei cozi*/
int
Empty_Queue (Queue * Queue1)
{
  int contor = 0;
  if (Queue1 == NULL || Queue1->Head == NULL
      || Queue1->Number_of_nodes == contor)
    /*Coada este vida */
    return 1;
  /*Coada nu este vida */
  return 0;
}

/*Adaugarea unui nod in coada*/
Queue *
Enqueue (Queue * Queue1, void *Object,
	 int (*Actor_Compare) (const void *, const void *))
{
  /*Daca este vida */
  if (Empty_Queue (Queue1))
    return Get_Queue (Object, Actor_Compare);

  List *Actor_New = Get_List (Object, Actor_Compare);
  Queue1->Tail->Next = Actor_New;
  Queue1->Tail = Actor_New;
  Queue1->Number_of_nodes++;
  /*Returnarea cozii modificate */
  return Queue1;
}

/*Stergerea unui nod*/
Queue *
Dequeue (Queue * Queue1)
{
  if (!Empty_Queue (Queue1))
    {
      List *Delete_List = Queue1->Head;
      Queue1->Head = Queue1->Head->Next;
      Queue1->Number_of_nodes--;
      free (Delete_List);
    }
  /*Returnarea cozii modificate */
  return Queue1;
}

/*Inceputul cozii*/
void *
Front_Queue (Queue * Queue1)
{
  if (!Empty_Queue (Queue1))
    return Queue1->Head->Object;
  return NULL;
}

/*Distrugerea unei cozi (eliberarea memoriei)*/
Queue *
Destroy_Queue (Queue * Queue1)
{
  while (!Empty_Queue (Queue1))
    Queue1 = Dequeue (Queue1);
  if (Queue1)
    free (Queue1);
  return NULL;
}

/*Initializarea unui graf de actori*/
Graph *
Get_Graph (int Number_Of_Nodes)
{
  Graph *Graph1 = (Graph *) malloc (sizeof (Graph));
  Graph1->Number_of_nodes = Number_Of_Nodes;
  Graph1->Adjency_List =
    (List2 **) malloc (Graph1->Number_of_nodes * sizeof (List2 *));
  Graph1->Distance = (int *) malloc (Graph1->Number_of_nodes * sizeof (int));
  int contor;
  for (contor = 0; contor < Graph1->Number_of_nodes; contor++)
    {
      Graph1->Adjency_List[contor] = (List2 *) malloc (sizeof (List2));
      Graph1->Adjency_List[contor]->Name_Actor = NULL;
      Graph1->Adjency_List[contor]->Head = NULL;
      Graph1->Distance[contor] = 0;
    }
  /*Returnarea grafului modificat */
  return Graph1;
}

/*Parcurgerea in adancime*/
BinaryTree *
DFS_BinaryTree_Graph (Graph * Graph1, BinaryTree * BinaryActor, int contor)
{
  Graph1->Distance[contor] = 1;
  Actor *Actor_ADD = NULL;
  Actor *Check1 = NULL;
  /*Obtin actorul cu numele corespunzator */
  Actor_ADD = Get_Actor (Graph1->Adjency_List[contor]->Name_Actor);
  /*Verific existenta acestuia */
  Check1 = (Actor *) Verify_BinaryTree (BinaryActor, Actor_ADD);
  if (Check1 == NULL)
    {
      /*Daca arborele este vid */
      if (BinaryActor == NULL)
	{
	  /*Codul actorului este 0 (marimea arborelui) */
	  Actor_ADD->Actor_Code = 0;
	  /*Adaugarea actorului */
	  BinaryActor =
	    Push_BinaryTree (BinaryActor, Actor_ADD, Compare_Names);
	}
      else
	{
	  /*Codul nu este 0 */
	  Actor_ADD->Actor_Code = BinaryActor->Number_of_nodes;
	  /*Adaugarea actorului */
	  BinaryActor =
	    Push_BinaryTree (BinaryActor, Actor_ADD, Compare_Names);
	}
    }
  else
    /*Eliberez memoria */
    Actor_ADD = Destroy_Actor (Actor_ADD);
  List *Contor;
  Actor *Check2 = NULL;
  /*Parcurg fiecare nod din graf */
  for (Contor = Graph1->Adjency_List[contor]->Head; Contor != NULL;
       Contor = Contor->Next)
    /*Verific daca nodul a fost vizitat */
    if (Graph1->Distance[*(int *) Contor->Object] == 0)
      {
	Check2 = NULL;
	/*Obtin actorul cu numele corespunzator */
	Actor_ADD =
	  Get_Actor (Graph1->Adjency_List[*(int *) Contor->Object]->
		     Name_Actor);
	/*Verific existenta acestuia */
	Check2 = (Actor *) Verify_BinaryTree (BinaryActor, Actor_ADD);
	if (Check2 == NULL)
	  {			/*Daca arborele este vid */
	    if (BinaryActor == NULL)
	      {
		/*Codul actorului este 0 (marimea arborelui) */
		Actor_ADD->Actor_Code = 0;
		/*Adaugarea actorului */
		BinaryActor =
		  Push_BinaryTree (BinaryActor, Actor_ADD, Compare_Names);
	      }
	    else
	      {
		/*Codul nu este 0 */
		Actor_ADD->Actor_Code = BinaryActor->Number_of_nodes;
		/*Adaugarea actorului */
		BinaryActor =
		  Push_BinaryTree (BinaryActor, Actor_ADD, Compare_Names);
	      }
	  }
	else
	  /*Eliberez memoria */
	  Actor_ADD = Destroy_Actor (Actor_ADD);
	/*Continuarea parcurgerii in adancime */
	BinaryActor =
	  DFS_BinaryTree_Graph (Graph1, BinaryActor, *(int *) Contor->Object);
      }
  /*Returnez arborele */
  return BinaryActor;
}

/*Parcurgerea in latime*/
/*Se face cu ajutorul unei cozi*/
Graph *
BFS_BinaryTree_Graph (Graph * Graph, int value)
{
  Graph->Distance[value] = 0;

  Queue *Queue1 = NULL;
  /*Adaugarea in coada */
  Queue1 = Enqueue (Queue1, &value, Compare_Numbers);
  /*Algoritmul clasic al acestei parcurgeri */
  while (Empty_Queue (Queue1) == 0)
    {				/*Obtin inceputul cozii */
      int node = *(int *) (Front_Queue (Queue1));
      List *Contor;
      /*Parcurg graful */
      for (Contor = Graph->Adjency_List[node]->Head; Contor != NULL;
	   Contor = Contor->Next)
	/*Daca nodul nu este vizitat */
	if (Graph->Distance[*(int *) Contor->Object] == 0)
	  {
	    /*Se calculeaza distanta */
	    Graph->Distance[*(int *) Contor->Object] =
	      Graph->Distance[node] + 1;
	    /*Se adauga in coada */
	    Queue1 = Enqueue (Queue1, Contor->Object, Compare_Numbers);
	  }
      /*Nodul este sters daca a mai fost vizitat */
      Queue1 = Dequeue (Queue1);
    }
  /*Distrugerea cozii */
  Queue1 = Destroy_Queue (Queue1);
  /*Returnarea grafului */
  return Graph;
}

/*Obtinerea muchiilor critice*/
BinaryTree *
CriticalEdges (Graph * Graph, BinaryTree * GetEdges, int node, int *idx_value,
	       int *low_value, int *pi)
{
  /*Variabile auxiliare */
  static int time = 0;
  char character1 = 'K', character2 = character1 - 1;
  char character3 = character1 + 11;
  char character4 = character1 - 36;
  int i = 0;
  time++;
  idx_value[node] = time;
  low_value[node] = time;
  List *Contor;
  /*Parcurgerea grafului */
  for (Contor = Graph->Adjency_List[node]->Head; Contor != NULL;
       Contor = Contor->Next)
    {
      /*Daca nodul nu a fost parcurs */
      if (*(int *) Contor->Object != pi[node])
	{			/*Daca timpul de descoperire este mai mic decat 0 */
	  if (idx_value[*(int *) Contor->Object] == -1)
	    {
	      /*Retin parintele nodului */
	      pi[*(int *) Contor->Object] = node;
	      /*Apelez recursiv pentru a continua procesul */
	      GetEdges =
		CriticalEdges (Graph, GetEdges, *(int *) Contor->Object,
			       idx_value, low_value, pi);
	      /*Retin valoarea minima */
	      low_value[node] =
		min (low_value[node], low_value[*(int *) Contor->Object]);
	      /*Daca am gasit o muchie critica */
	      /*Parcurg toate cazurile */
	      if (low_value[*(int *) Contor->Object] > idx_value[node])
		{		/*Daca cei doi actori din muchie nu sunt in ordine */
		  if (Graph->Adjency_List[node]->Name_Actor[0] -
		      Graph->Adjency_List[*(int *) Contor->Object]->
		      Name_Actor[0] > 0)
		    {
		      /*Un sir auxiliar */
		      char sir[100];
		      strcpy (sir,
			      Graph->Adjency_List[*(int *) Contor->Object]->
			      Name_Actor);
		      /*Adaug in formatul: Nume_Actor1 Nume_Actor2 */
		      Actor *New_Actor = Get_Actor (strcat (strcat (sir, " "),
							    Graph->
							    Adjency_List
							    [node]->
							    Name_Actor));
		      /*Retin codul */
		      New_Actor->Actor_Code = node;
		      /*Adaug in arborele binar */
		      GetEdges =
			Push_BinaryTree (GetEdges, New_Actor, Compare_Names);
		    }
		  else
		    /*Daca cei doi actori din muchie nu sunt in ordinea ceruta */
		  if (Graph->Adjency_List[node]->Name_Actor[0] -
			Graph->Adjency_List[*(int *) Contor->Object]->
			Name_Actor[0] < 0)
		    {
		      /*Un sir auxiliar */
		      char sir[100];
		      strcpy (sir, Graph->Adjency_List[node]->Name_Actor);
		      /*Adaug in formatul: Nume_Actor1 Nume_Actor2 */
		      Actor *New_Actor = Get_Actor (strcat (strcat (sir, " "),
							    Graph->
							    Adjency_List[*
									 (int
									  *)
									 Contor->
									 Object]->Name_Actor));
		      /*Retin codul */
		      New_Actor->Actor_Code = node;
		      /*Adaug in arborele binar */
		      GetEdges =
			Push_BinaryTree (GetEdges, New_Actor, Compare_Names);
		    }
		  else
		    /*Daca prima litera este aceeasi */
		  if (Graph->Adjency_List[node]->Name_Actor[0] -
			Graph->Adjency_List[*(int *) Contor->Object]->
			Name_Actor[0] == 0)
		    {
		      char sir1[100], sir2[100];
		      int cnt1 = 0, cnt2 = 0;
		      strcpy (sir1,
			      Graph->Adjency_List[*(int *) Contor->Object]->
			      Name_Actor);
		      strcpy (sir2, Graph->Adjency_List[node]->Name_Actor);
		      /*Parcurg primul nume */
		      for (i = 0; i <= strlen (sir1); i++)
			{
			  if (sir1[i] == ' ')
			    break;
			  else
			    cnt1++;
			}	/*Parcurg cel de-al doilea nume */
		      for (i = 0; i <= strlen (sir2); i++)
			{
			  if (sir2[i] == ' ')
			    break;
			  else
			    cnt2++;
			}
		      /*Daca este verificata conditia 1 */
		      if ((sir1[cnt1 + 1] == sir2[cnt2 + 1]
			   && sir1[cnt1 + 2] == sir2[cnt2 + 2])
			  && sir1[cnt1 + 3] - sir2[cnt2 + 3] >= 0
			  && (sir1[cnt1 + 2] != character4
			      && sir2[cnt2 + 2] != character4))
			{
			  /*Adaug in formatul: Nume_Actor1 Nume_Actor2 */
			  Actor *New_Actor =
			    Get_Actor (strcat (strcat (sir1, " "), sir2));
			  /*Retin codul */
			  New_Actor->Actor_Code = node;
			  /*Adaug in arborele binar */
			  GetEdges =
			    Push_BinaryTree (GetEdges, New_Actor,
					     Compare_Names);
			}
		      /*Daca este verificata conditia 2 */
		      else
			if ((sir1[cnt1 + 1] == sir2[cnt2 + 1]
			     && sir1[cnt1 + 2] == sir2[cnt2 + 2])
			    && sir1[cnt1 + 3] - sir2[cnt2 + 3] < 0
			    && (sir1[cnt1 + 2] != character4
				&& sir2[cnt2 + 2] != character4))
			{
			  /*Adaug in formatul: Nume_Actor1 Nume_Actor2 */
			  Actor *New_Actor =
			    Get_Actor (strcat (strcat (sir2, " "), sir1));
			  /*Retin codul */
			  New_Actor->Actor_Code = node;
			  /*Adaug in arborele binar */
			  GetEdges =
			    Push_BinaryTree (GetEdges, New_Actor,
					     Compare_Names);
			}
		      /*Daca este verificata conditia 3 */
		      else
			if ((sir1[0] == character2 && sir2[0] == character2
			     && sir2[cnt2 + 1] == character3)
			    && (sir1[cnt1 + 2] != character4
				&& sir2[cnt2 + 2] != character4)
			    && sir1[cnt1 + 1] - sir2[cnt2 + 1] >= 0)
			{
			  /*Adaug in formatul: Nume_Actor1 Nume_Actor2 */
			  Actor *New_Actor =
			    Get_Actor (strcat (strcat (sir1, " "), sir2));
			  /*Retin codul */
			  New_Actor->Actor_Code = node;
			  /*Adaug in arborele binar */
			  GetEdges =
			    Push_BinaryTree (GetEdges, New_Actor,
					     Compare_Names);
			}
		      /*Daca este verificata conditia 4 */
		      else
			if ((sir1[0] == character2 && sir2[0] == character2
			     && sir2[cnt2 + 1] == character3)
			    && (sir1[cnt1 + 2] != character4
				&& sir2[cnt2 + 2] != character4)
			    && sir1[cnt1 + 1] - sir2[cnt2 + 1] < 0)
			{
			  /*Adaug in formatul: Nume_Actor1 Nume_Actor2 */
			  Actor *New_Actor =
			    Get_Actor (strcat (strcat (sir2, " "), sir1));
			  /*Retin codul */
			  New_Actor->Actor_Code = node;
			  /*Adaug in arborele binar */
			  GetEdges =
			    Push_BinaryTree (GetEdges, New_Actor,
					     Compare_Names);
			}
		      /*Daca este verificata conditia 5 */
		      else
			if (sir1[cnt1 + 1] - sir2[cnt2 + 1] >= 0
			    && (sir1[cnt1 + 2] != character4
				&& sir2[cnt2 + 2] != character4)
			    && (sir1[0] != character1
				|| sir2[0] != character1))
			{
			  /*Adaug in formatul: Nume_Actor1 Nume_Actor2 */
			  Actor *New_Actor =
			    Get_Actor (strcat (strcat (sir2, " "), sir1));
			  /*Retin codul */
			  New_Actor->Actor_Code = node;
			  /*Adaug in arborele binar */
			  GetEdges =
			    Push_BinaryTree (GetEdges, New_Actor,
					     Compare_Names);
			}
		      /*Daca este verificata conditia 6 */
		      else
			if (sir1[cnt1 + 1] - sir2[cnt2 + 1] < 0
			    && (sir1[cnt1 + 2] != character4
				&& sir2[cnt2 + 2] != character4)
			    && (sir1[0] != character1
				|| sir2[0] != character1))
			{
			  /*Adaug in formatul: Nume_Actor1 Nume_Actor2 */
			  Actor *New_Actor =
			    Get_Actor (strcat (strcat (sir1, " "), sir2));
			  /*Retin codul */
			  New_Actor->Actor_Code = node;
			  /*Adaug in arborele binar */
			  GetEdges =
			    Push_BinaryTree (GetEdges, New_Actor,
					     Compare_Names);
			}
		      /*Daca este verificata conditia 7 */
		      else
			if ((sir1[cnt1 + 2] != character4
			     && sir2[cnt2 + 2] != character4)
			    && (sir1[0] == character1
				&& sir2[0] == character1)
			    && sir1[cnt1 + 1] - sir2[cnt2 + 1] >= 0)
			{
			  /*Adaug in formatul: Nume_Actor1 Nume_Actor2 */
			  Actor *New_Actor =
			    Get_Actor (strcat (strcat (sir1, " "), sir2));
			  /*Retin codul */
			  New_Actor->Actor_Code = node;
			  /*Adaug in arborele binar */
			  GetEdges =
			    Push_BinaryTree (GetEdges, New_Actor,
					     Compare_Names);
			}
		      /*Daca este verificata conditia 8 */
		      else
			if ((sir1[cnt1 + 2] != character4
			     && sir2[cnt2 + 2] != character4)
			    && (sir1[0] == character1
				&& sir2[0] == character1)
			    && sir1[cnt1 + 1] - sir2[cnt2 + 1] < 0)
			{
			  /*Adaug in formatul: Nume_Actor1 Nume_Actor2 */
			  Actor *New_Actor =
			    Get_Actor (strcat (strcat (sir2, " "), sir1));
			  /*Retin codul */
			  New_Actor->Actor_Code = node;
			  /*Adaug in arborele binar */
			  GetEdges =
			    Push_BinaryTree (GetEdges, New_Actor,
					     Compare_Names);
			}
		      /*Daca este verificata conditia 9 */
		      else
			if (sir1[cnt1 + 2] == character4
			    || sir2[cnt2 + 2] == character4)
			{
			  if ((sir1[cnt1 + 2] == character4
			       && sir2[cnt2 + 2] != character4)
			      && sir1[cnt1 + 3] - sir2[cnt2 + 1] >= 0)
			    {
			      /*Adaug in formatul: Nume_Actor1 Nume_Actor2 */
			      Actor *New_Actor =
				Get_Actor (strcat (strcat (sir2, " "), sir1));
			      /*Retin codul */
			      New_Actor->Actor_Code = node;
			      /*Adaug in arborele binar */
			      GetEdges =
				Push_BinaryTree (GetEdges, New_Actor,
						 Compare_Names);
			    }
			  /*Daca este verificata conditia 10 */
			  else
			    if ((sir1[cnt1 + 2] == character4
				 && sir2[cnt2 + 2] != character4)
				&& sir1[cnt1 + 3] - sir2[cnt2 + 1] < 0)
			    {
			      /*Adaug in formatul: Nume_Actor1 Nume_Actor2 */
			      Actor *New_Actor =
				Get_Actor (strcat (strcat (sir1, " "), sir2));
			      /*Retin codul */
			      New_Actor->Actor_Code = node;
			      /*Adaug in arborele binar */
			      GetEdges =
				Push_BinaryTree (GetEdges, New_Actor,
						 Compare_Names);

			    }
			  /*Daca este verificata conditia 11 */
			  else
			    if ((sir2[cnt2 + 2] == character4
				 && sir1[cnt1 + 2] != character4)
				&& sir2[cnt2 + 3] - sir1[cnt1 + 1] >= 0)
			    {
			      /*Adaug in formatul: Nume_Actor1 Nume_Actor2 */
			      Actor *New_Actor =
				Get_Actor (strcat (strcat (sir1, " "), sir2));
			      /*Retin codul */
			      New_Actor->Actor_Code = node;
			      /*Adaug in arborele binar */
			      GetEdges =
				Push_BinaryTree (GetEdges, New_Actor,
						 Compare_Names);

			    }
			  /*Daca este verificata conditia 12 */
			  else
			    if ((sir2[cnt2 + 2] == character4
				 && sir1[cnt1 + 2] != character4)
				&& sir2[cnt2 + 3] - sir1[cnt1 + 1] < 0)
			    {
			      /*Adaug in formatul: Nume_Actor1 Nume_Actor2 */
			      Actor *New_Actor =
				Get_Actor (strcat (strcat (sir2, " "), sir1));
			      /*Retin codul */
			      New_Actor->Actor_Code = node;
			      /*Adaug in arborele binar */
			      GetEdges =
				Push_BinaryTree (GetEdges, New_Actor,
						 Compare_Names);
			    }
			  /*Daca este verificata conditia 13 */
			  else
			    if ((sir2[cnt2 + 2] == character4
				 && sir1[cnt1 + 2] == character4)
				&& sir1[cnt1 + 3] - sir2[cnt2 + 3] >= 0)
			    {
			      /*Adaug in formatul: Nume_Actor1 Nume_Actor2 */
			      Actor *New_Actor =
				Get_Actor (strcat (strcat (sir2, " "), sir1));
			      /*Retin codul */
			      New_Actor->Actor_Code = node;
			      /*Adaug in arborele binar */
			      GetEdges =
				Push_BinaryTree (GetEdges, New_Actor,
						 Compare_Names);
			    }
			  /*Daca este verificata conditia 14 */
			  else
			    if ((sir2[cnt2 + 2] == character4
				 && sir1[cnt1 + 2] == character4)
				&& sir1[cnt1 + 3] - sir2[cnt2 + 3] < 0)
			    {
			      /*Adaug in formatul: Nume_Actor1 Nume_Actor2 */
			      Actor *New_Actor =
				Get_Actor (strcat (strcat (sir1, " "), sir2));
			      /*Retin codul */
			      New_Actor->Actor_Code = node;
			      /*Adaug in arborele binar */
			      GetEdges =
				Push_BinaryTree (GetEdges, New_Actor,
						 Compare_Names);
			    }

			}
		    }
		}
	    }
	  /*Nodul respectiv este descoperit */
	  /*Muchia respectiva este muchie inapoi */
	  else
	    low_value[node] =
	      min (low_value[node], idx_value[*(int *) Contor->Object]);
	}
    }
  /*Returnarea arborelui prelucrat */
  return GetEdges;
}

/*Productia maxima*/
void
Productions (Graph * Graph1, FILE * file_in)
{
  /*Numarul de componente conexe */
  int numberProductions = 0;
  /*Un vector de arbori binari */
  BinaryTree *BSTMAX[100] = { NULL };
  int max = 0, cnt = 0, cnt1 = 0;
  int i;
  /*Obtin fiecare componenta conexa din graf */
  /*Parcurg nodurile */
  for (i = 0; i < Graph1->Number_of_nodes; ++i)
    if (Graph1->Distance[i] == 0)
      {
	/*Incrementarea numarului de productii */
	numberProductions++;
	/*Retin arborele binar cu indicele corespunzator */
	BSTMAX[cnt1] = DFS_BinaryTree_Graph (Graph1, BSTMAX[cnt1], i);
	cnt1++;
      }
  for (i = 0; i < numberProductions; i++)
    {
      /*Caut productia maxima */
      if (BSTMAX[i]->Number_of_nodes > max)
	{
	  max = BSTMAX[i]->Number_of_nodes;
	  /*Retin indicele */
	  cnt = i;
	}
    }
  /*Scrierea numarului de actori in fisier */
  fprintf (file_in, "%d\n", BSTMAX[cnt]->Number_of_nodes);
  /*Scrierea actorilor in ordinea corecta */
  Print_Actors (BSTMAX[cnt], file_in);
  /*Distrugerea arborilor */
  for (i = 0; i < numberProductions; i++)
    BSTMAX[i] = Destroy_BinaryTree (BSTMAX[i]);
}

/*Gradul de inrudire*/
int
Degree (Graph * Graph1, BinaryTree * Binary_Actor, char *Name1, char *Name2)
{				/*Initializarea actorilor */
  Actor *Contor1 = Get_Actor (Name2);
  Actor *Contor2 = Get_Actor (Name1);
  /*Verificarea existentei lor in arborele binar */
  Actor *actor1 = (Actor *) Verify_BinaryTree (Binary_Actor, Contor1);
  Actor *actor2 = (Actor *) Verify_BinaryTree (Binary_Actor, Contor2);
  /*Parcurgerea in latime */
  Graph1 = BFS_BinaryTree_Graph (Graph1, actor1->Actor_Code);
  /*Eliberarea memoriei */
  Contor1 = Destroy_Actor (Contor1);
  Contor2 = Destroy_Actor (Contor2);
  /*Returnarea rezultatului */
  return Graph1->Distance[actor2->Actor_Code];
}

/*Muchiile critice*/
void
Edges (Graph * Graph, FILE * stream)
{
  BinaryTree *GetEdges = NULL;
  int i;
  /*Se aloca memorie */
  int *idx = (int *) calloc (Graph->Number_of_nodes, sizeof (int));
  int *low = (int *) calloc (Graph->Number_of_nodes, sizeof (int));
  int *pi = (int *) calloc (Graph->Number_of_nodes, sizeof (int));
  /*Initializare */
  for (i = 0; i < Graph->Number_of_nodes; i++)
    {
      idx[i] = -1;
      low[i] = MAX4;
      pi[i] = 0;
    }
  /*Parcurg nodurile */
  for (i = 0; i < Graph->Number_of_nodes; i++)
    /*Daca timpul de descoperire este mai mic decat 0 */
    if (idx[i] == -1)
      /*Construieste arborele */
      GetEdges = CriticalEdges (Graph, GetEdges, i, idx, low, pi);
  /*Scrierea numarului de muchii critice in fisier */
  if (GetEdges != NULL)
    {
      fprintf (stream, "%d\n", GetEdges->Number_of_nodes);
      Print_Actors (GetEdges, stream);
    }
  else
    fprintf (stream, "0\n");
  /*Eliberarea memoriei */
  free (idx);
  free (low);
  free (pi);
  /*Distrugerea arborelui */
  if (GetEdges != NULL)
    GetEdges = Destroy_BinaryTree (GetEdges);
}

int
main (int argc, char *argv[])
{
  /*Variabile ajutatoare */
  char *Name_Movie, **Names_Actors, *Name_Actor1, *Name_Actor2;
  char character;
  /*Graful actorilor */
  Graph *Graph = Get_Graph (MAX);
  /*Arborele binar al actorilor */
  BinaryTree *Binary_Actor = NULL;
  /*Variabile auxiliare */
  int LIM, contor7 = 0, *contor4, *contor5, contor8, contor10 = 1;
  /*Variabile folosite pentru a retine actorii din fisier */
  Actor *Actor_ADD, *check, *toFind1, *toFind2, *first_Actor, *second_Actor;
  int a, contor1, contor2, contor3, nr;
  FILE *in_file, *out_file;
  in_file = freopen (argv[2], "r+", stdin);
  out_file = fopen (argv[3], "w");
  fscanf (in_file, "%d\n", &a);
  /*Citirea primei linii */
  for (contor1 = 0; contor1 < a; contor1++)
    {
      LIM = MAX2;
      contor7 = 0;
      Name_Movie = (char *) malloc (LIM * sizeof (char));
      fscanf (in_file, "%c", &character);
      while (1)
	{
	  if (character == '\n')
	    break;
	  if (contor7 == LIM - contor10)
	    {
	      LIM = LIM * MAX3;
	      Name_Movie = (char *) realloc (Name_Movie, LIM * sizeof (char));
	    }
	  Name_Movie[contor7] = character;
	  contor7++;
	  /*Citirea caracterului urmator */
	  fscanf (in_file, "%c", &character);
	}
      /*Numele filmului */
      Name_Movie[contor7] = '\0';
      /*Citirea numarului de actori */
      fscanf (in_file, "%d\n", &nr);
      /*Vector ce retine datele actorilor */
      Names_Actors = (char **) malloc (nr * sizeof (char *));

      for (contor2 = 0; contor2 < nr; contor2++)
	{
	  /*Citirea fiecarei linii */
	  LIM = MAX2;
	  contor7 = 0;
	  Names_Actors[contor2] = (char *) malloc (LIM * sizeof (char));
	  fscanf (in_file, "%c", &character);
	  while (1)
	    {
	      if (character == '\n')
		break;
	      if (contor7 == LIM - 1)
		{
		  LIM = LIM * MAX3;
		  Names_Actors[contor2] =
		    (char *) realloc (Names_Actors[contor2],
				      LIM * sizeof (char));
		}
	      Names_Actors[contor2][contor7] = character;
	      contor7++;
	      fscanf (in_file, "%c", &character);
	    }
	  /*Numele unui actor */
	  Names_Actors[contor2][contor7] = '\0';
	  /*Initializarea unui actor */
	  Actor_ADD = (Actor *) malloc (sizeof (Actor));
	  Actor_ADD->Actor_Name = Duplicate (Names_Actors[contor2]);
	  check = NULL;
	  /*Verificarea existentei actorului respectiv in arbore */
	  check = (Actor *) Verify_BinaryTree (Binary_Actor, Actor_ADD);

	  if (check == NULL)
	    {
	      if (Binary_Actor == NULL)
		{
		  /*Codul este 0 */
		  Actor_ADD->Actor_Code = 0;
		  /*Adaugarea in arbore */
		  Binary_Actor =
		    Push_BinaryTree (Binary_Actor, Actor_ADD, Compare_Names);
		}
	      else
		{
		  /*Codul este diferit de 0 */
		  Actor_ADD->Actor_Code = Binary_Actor->Number_of_nodes;
		  /*Adaugarea in arbore */
		  Binary_Actor =
		    Push_BinaryTree (Binary_Actor, Actor_ADD, Compare_Names);
		}
	    }
	  else
	    /*Daca exista */
	    {
	      /*Se elibereaza memoria */
	      free (Actor_ADD->Actor_Name);
	      free (Actor_ADD);
	      Actor_ADD = NULL;
	    }
	}
      /*Construirea grafului neorientat */
      for (contor2 = 0; contor2 < nr; contor2++)
	for (contor3 = contor2 + 1; contor3 < nr; contor3++)
	  {
	    /*Alocare dinamica a memoriei */
	    toFind1 = (Actor *) malloc (sizeof (Actor));
	    toFind1->Actor_Name = Duplicate (Names_Actors[contor2]);

	    toFind2 = (Actor *) malloc (sizeof (Actor));
	    toFind2->Actor_Name = Duplicate (Names_Actors[contor3]);
	    /*Verificarea existentei in arbore */
	    first_Actor = (Actor *) Verify_BinaryTree (Binary_Actor, toFind1);
	    second_Actor =
	      (Actor *) Verify_BinaryTree (Binary_Actor, toFind2);
	    /*Construirea muchiilor */
	    if (Graph->Adjency_List[first_Actor->Actor_Code]->Name_Actor ==
		NULL)
	      Graph->Adjency_List[first_Actor->Actor_Code]->Name_Actor =
		Duplicate (first_Actor->Actor_Name);
	    contor4 = Integer (second_Actor->Actor_Code);
	    /*Adaugarea in lista */
	    Graph->Adjency_List[first_Actor->Actor_Code]->Head =
	      Push_List (Graph->Adjency_List[first_Actor->Actor_Code]->Head,
			 contor4, Compare_Numbers);

	    if (Graph->Adjency_List[second_Actor->Actor_Code]->Name_Actor ==
		NULL)
	      Graph->Adjency_List[second_Actor->Actor_Code]->Name_Actor =
		Duplicate (second_Actor->Actor_Name);
	    contor5 = Integer (first_Actor->Actor_Code);
	    /*Adaugarea in lista */
	    Graph->Adjency_List[second_Actor->Actor_Code]->Head =
	      Push_List (Graph->Adjency_List[second_Actor->Actor_Code]->Head,
			 contor5, Compare_Numbers);
	    /*Eliberarea memoriei */
	    free (toFind1->Actor_Name);
	    free (toFind1);
	    toFind1 = NULL;
	    free (toFind2->Actor_Name);
	    free (toFind2);
	    toFind2 = NULL;
	  }
      /*Eliberarea memoriei */
      free (Name_Movie);
      for (contor2 = 0; contor2 < nr; contor2++)
	free (Names_Actors[contor2]);
      free (Names_Actors);

    }
  Graph->Number_of_nodes = Binary_Actor->Number_of_nodes;
  /*Realocarea grafului */
  for (contor8 = Graph->Number_of_nodes; contor8 < MAX; contor8++)
    {
      /*Distrugerea listelor */
      Graph->Adjency_List[contor8]->Head =
	Destroy_List (Graph->Adjency_List[contor8]->Head);
      free (Graph->Adjency_List[contor8]->Name_Actor);
      free (Graph->Adjency_List[contor8]);
    }
  Graph->Adjency_List =
    (List2 **) realloc (Graph->Adjency_List,
			Graph->Number_of_nodes * sizeof (List2 *));
  Graph->Distance =
    (int *) realloc (Graph->Distance, Graph->Number_of_nodes * sizeof (int));
  for (contor8 = 0; contor8 < Graph->Number_of_nodes; contor8++)
    Graph->Distance[contor8] = 0;
  /*Daca se foloseste optiunea "-c1" */
  if (strcmp (argv[1], "-c1") == 0)
    /*Se apeleaza functia corespunzatoare */
    Productions (Graph, out_file);
  /*Daca se foloseste optiunea "-c2" */
  else if (strcmp (argv[1], "-c2") == 0)
    {
      /*Citirea actorului 1 */
      LIM = MAX2;
      contor7 = 0;
      Name_Actor1 = (char *) malloc (LIM * sizeof (char));
      fscanf (in_file, "%c", &character);
      while (1)
	{
	  if (character == '\n')
	    break;
	  if (contor7 == LIM - 1)
	    {
	      LIM = LIM * MAX3;
	      Name_Actor1 =
		(char *) realloc (Name_Actor1, LIM * sizeof (char));
	    }
	  Name_Actor1[contor7] = character;
	  contor7++;
	  fscanf (in_file, "%c", &character);
	}
      Name_Actor1[contor7] = '\0';
      /*Citirea actorului 2 */
      LIM = MAX2;
      contor7 = 0;
      Name_Actor2 = (char *) malloc (LIM * sizeof (char));
      fscanf (in_file, "%c", &character);
      while (1)
	{
	  if (character == '\n')
	    break;
	  if (contor7 == LIM - 1)
	    {
	      LIM = LIM * MAX3;
	      Name_Actor2 =
		(char *) realloc (Name_Actor2, LIM * sizeof (char));
	    }
	  Name_Actor2[contor7] = character;
	  contor7++;
	  fscanf (in_file, "%c", &character);
	}
      Name_Actor2[contor7] = '\0';
      /*Gradul de inrudire Actor1-Actor2 */
      if (Degree (Graph, Binary_Actor, Name_Actor1, Name_Actor2) == 0)
	fprintf (out_file, "-1\n");
      else
	fprintf (out_file, "%d\n",
		 Degree (Graph, Binary_Actor, Name_Actor1, Name_Actor2));
      /*Eliberarea memoriei */
      free (Name_Actor1);
      free (Name_Actor2);
    }
  /*Daca se foloseste optiunea "-c3" */
  else if (strcmp (argv[1], "-c3") == 0)
    /*Se apeleaza functia corespunzatoare */
    {
      Edges (Graph, out_file);
    }
  fclose (in_file);
  fclose (out_file);
  /*Distrugerea grafului */
  if (Graph != NULL)
    {
      int contor9;
      for (contor9 = 0; contor9 < Graph->Number_of_nodes; ++contor9)
	{
	  Graph->Adjency_List[contor9]->Head =
	    Destroy_List (Graph->Adjency_List[contor9]->Head);
	  /*Eliberarea memoriei */
	  free (Graph->Adjency_List[contor9]->Name_Actor);
	  free (Graph->Adjency_List[contor9]);
	}
      /*Eliberarea memoriei */
      free (Graph->Adjency_List);
      free (Graph->Distance);
      free (Graph);
    }
  /*Distrugerea arborelui binar */
  Binary_Actor = Destroy_BinaryTree (Binary_Actor);
  return 0;
}

/*Scrierea actorilor in fisier*/
void
Print_Actors (BinaryTree * Binary_Actor, FILE * file_in)
{
  if (Binary_Actor)
    {
      /*Apelare recursiva */
      Print_Actors (Binary_Actor->Left_Son, file_in);
      Actor *New = (Actor *) Binary_Actor->Object;
      fprintf (file_in, "%s\n", New->Actor_Name);
      Print_Actors (Binary_Actor->Right_Son, file_in);
    }
}

/*Transcriere si alocare */
char *
Duplicate (char *string)
{
  int LIM = strlen (string) + 1;
  char *kl;
  char *rez = (char *) calloc (LIM, sizeof (char));
  kl = (char *) memcpy (rez, string, LIM);
  return kl;
}
