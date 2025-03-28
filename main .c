#include<stdio.h>
#include<string.h>
#include<ctype.h> //para utilizar o isdigit()
#include <locale.h>
#include <time.h>
#include <stdlib.h>

/*
  RPG Interativo - Achemist Tale
  Contratante    : Immersive Digital Play (IDP)
  Desenvolvedores: Larissa Böhm
*/


#define TAM_persona 3
#define TAM_charada  10

struct tipo_persona
{
  char sNm[21];	//Nome
  int  iRc;	    //Raça
  int  iAl;	    //Alinhamento
  int  iPf;	    //Profissão
  int  iMt;	    //Meta
  int  iMv;	    //Meio em que vive
  int  iPt;	    //Porte
  int  iVd;  	  //Vida
};

typedef struct tipo_persona tipo_persona;

int   iTl_persona[TAM_persona], iTl_charada[TAM_charada], iCPclose=0, iCPcRepeat=0, iEvtPersona=0;

char  cMrc[3][20]={"Humano","Anao","Elfo"},
      cMal[3][20]={"Mal","Neutro","Bom"},
      cMpf[3][20]={"Guerreio","Mago","Ladino"},
      cMmt[3][20]={"Governar o reino","Ficar rico","Destruir o mal"},
      cMmv[3][20]={"Urbano","Rural","Tribal"},
      cMpt[3][20]={"Grande","Medio","Pequeno"};

char  cTcd1[17][70]=
      {"*       Há muito tempo, a terra era dominada por:           *",
      "*              humanos,anões e elfos.                       *",
      "* Os seres mitológicos como fadas e dragões conviviam em    *",
      "* harmonia e compartilhavam seus dons e habilidades.  Os    *",
      "* castelos eram construídos com torres majestosas, e nas    *",
      "* bibliotecas  ocultas guardavam-se seções   ancestrais,    *",
      "* contendo sabedoria que passou de geração a geração.       *",
      "* No entanto, nem tudo é tranquilidade, um buraco surgiu    *",
      "* no planeta e aumentou até ocorrer uma explosão.           *",
      "* A chegada de criaturas obscuras  de um  lugar distante    *",
      "* ameaçou a harmonia e o futuro da  terra.  Contaminados    *",
      "* por um vírus desconhecido e à procura do elixir da vida   *",
      "* (capaz de curar qualquer doença) esses seres eram capazes *",
      "* de disseminar um mal irreversível. Agora,caro jogador,é a *",
      "* sua hora de decidir o destino do planeta. Explore terras, *",
      "* embarque em missões emocionantes e descubra segredos há   *",
      "* muito tempo esquecidos. O futuro está em suas mãos.       *"},
//
    cTcd2[2][70]=
    {"*     Preste atenção na história e em seus personagens.     *",
     "*      Existe um rumor de que será útil futuramente.        *"},
//
    cTev1[9][70]=
    {"*  Em uma de suas aventuras, você escuta a conversa de um   *",  
     "*  velho Dragão conhecido como “O Sábio” com uma fada azul  *",
     "*  chamada “Aurora” sobre rumores de um templo assombrado.  *",
     "*  Segundo as mais antigas lendas,  nesse templo  está  o   *",
     "*  elixir da vida, e nenhuma criatura se provou corajosa,   *",
     "*  habilidosa ou digna de conseguir vencer os desafios.     *",
     "*  A sua ambição, jogador, te leva ao local do templo       *",
     "*  assombrado. Lá você se depara com um bruxo vestido com   *",
     "*  um manto antigo ele lhe oferece 3 caminhos possíveis:    *"},
//
    cTev2[8][60]=
    {"*  Após sua jornada  bem-sucedida  em obter  o *",
     "*  poderoso Elixir da Vida, você vai à procura *", 
     "*  do Rei para formar uma aliança poderosa.    *",
     "*  Quando você chega no castelo Real, uma fada *", 
     "*  vai ao seu encontro e te fala que o Rei se  *", 
     "*  corrompeu, e está te procurando para roubar *", 
     "*  o elixir. Você não pode permitir que isso   *", 
     "*  aconteça.                                   *"},
// 
    cTev3[6][60]=
    {"* Você obteve sucesso em proteger  o elixir,  e   *",
     "* agora você descobre uma  informação capaz  de   *",
     "* expulsar os extraterrestres da terra, contida   *",
     "* no  castelo  do  Rei, porém  essas  criaturas   *",
     "* descobrem que você tem o elixir e te encontram. *",
     "* Eles falam que infectaram o seu  amigo dragão.  *"},
//
    cTev4[8][60]=
    {"*  Após  uma  série de  eventos desafiadores,     *",
     "*  você se  encontra  diante do Rei, que está     *",
     "*  visivelmente  furioso   com   suas   ações     *",
     "*  anteriores. Ele está determinado a puni-lo     *",
     "*  de   alguma  forma,  mas você  propõe  uma     *",
     "*  alternativa:um jogo de Jokenpô para decidir    *",
     "*  o seu destino.O Rei concorda com a proposta    *",
     "*  e vocês se preparam para a disputa.            *"},
//
    cTev41[4][60]=
    {"*  O Jokenpô é  um  jogo simples, em  que cada    *",
     "*  jogador escolhe entre Pedra, Papel ou Tesoura. *",
     "*  As regras são claras:  Pedra  vence  Tesoura,  *",
     "*  Tesoura  vence  Papel  e  Papel  vence Pedra.  *"},
//
    cTev5[8][60]=
    {"*  Após uma longa jornada e inúmeros desafios, *",
     "*  você finalmente chega  ao  confronto final  *",
     "*  contra  o  líder  dos extraterrestres, uma  *",
     "*  criatura poderosa e misteriosa.             *",
     "*  No  entanto, o  líder  extraterrestre não   *",
     "*  pretende enfrentá-lo em um combate direto.  *",
     "*  Em vez disso, ele desafia você a resolver   *",
     "*  três charadas.                              *"},
//
    cTev6[7][60]=
    {"* Com as  três charadas resolvidas  com sabedoria e  *",
     "* precisão,  o líder dos extraterrestres  reconhece  *",
     "* sua  inteligência  e  dignidade  como  adversário. *",
     "* Ele admite que subestimou a força e a determinação *",
     "* da humanidade e decide encerrar a invasão à Terra. *",
     "* Parabéns, você tem o controle do elixir da vida e  *",
     "* alcançou suas metas e objetivos.                   *"},
//
    cTev6C1[10][100] =
    {" Que personagens estavam conversando sobre o templo assombrado? ",
     " Como o dragão era conhecido?  ",
     " O que o Templo assombrado guarda? ", 
     " Qual era o nome da fada Azul? ",
     " Como o bruxo estava vestido? ",
     " O que o elixir da vida era capaz de fazer? ",
     " Quem te contou que o Rei se corrompeu? ",
     " Qual amigo seu foi infectado pelas criaturas malignas? ",
     " Quem te desafiou a jogar Jokenpô? ",
     " Qual criatura poderosa o desafiou a resolver charadas? "},
//
    cTev6Op[10][110] =
    {
      "    1 - Dragão e fada\n    2 - Humano e elfo\n    3 - Fada e Anão\n",
      "    1 - O Grande\n    2 - O Sábio\n    3 - O Esperto\n",
      "    1 - O elixir da vida\n    2 - O livro dos mistérios\n    3 - Os segredos mais sombrios da Terra\n",
      "    1 - Aurora\n    2 - Bela\n    3 - Jasmine\n",
      "    1 - Com um manto antigo\n    2 - Com um manto azul\n    3 - Com um manto preto\n",
      "    1 - Derrotar o mal\n    2 - Curar todas as doenças\n    3 - Realizar desejos\n",
      "    1 - uma fada\n    2 - Um dragão\n    3 - Um bruxo\n",
      "    1 - um elfo\n    2 - Um dragão\n    3 - Um humano\n",
      "    1 - O rei\n    2 - A rainha\n    3 - A princesa\n",
      "    1 - O rei\n    2 - O líder da guarda-real\n    3 - O líder dos extraterrestres\n",
    },
//   
    cTev6Resp[10]={1,2,1,1,1,2,1,2,1,3};


tipo_persona lista_persona[TAM_persona];


void inicializa_jogo(void);
char menu(void);
char valida_menu(char cFvmOpcao);
char menu_raca(void);
char menu_alinhamento(void);
char menu_profissao(int iAl);
char menu_meta(int iAl);
char menu_meio(int iPf);
char menu_porte(int iRc);
int  conta_persona();
char cadastra_persona(int iCPersona);
char menu_persona(void);
char valida_menu_persona(char cFvmpOpcao);
char altera_cadastro(int iCPersona);
char menu_eventos(int iEvt);
char lista_evento(int iFevt);
char jogar_jokenpo(void);
char lista_charadas(void);

int main()
{ 
  setlocale(LC_ALL, "Portuguese");
  srand(time(NULL)); 

  char cMOpcao='0', cVOpcao='0', sNome[21], cVcp='0', cMaOpcao='0', cVmaOpcao='0', cVmacp='0', cMevtOpcao='0';
  char *t;
  int  iCPersona=0, iAPersona=0, iAltera=0, iPerJoga=0, iTcd1, indEvt = 0;

  inicializa_jogo();
  
  do
  {
    printf("\n");
    cMOpcao = menu();
    cVOpcao = valida_menu(cMOpcao);
//
    switch (cVOpcao)
    {
      case '1':
        if (iCPclose !=0) 
        {
          int system();
          system("clear");
          printf("\n********              Cadastro Concluído                ********");
          printf("\n********        Escolha um Personagem para Jogar        ********");
          if (iCPcRepeat==0) 
          {
            iCPcRepeat=1;
          }
          else
          {
            printf("\n********              Não Adianta Insistir              ********");      
          }
        } 
        else 
        {
          iCPersona=0;
          iCPersona=conta_persona();

          if (iCPersona < TAM_persona)
          {
            system("clear");
            cVcp = cadastra_persona(iCPersona);
//
            if (cVcp != 'S') 
            {
              printf("\nTente Novamente antes de inicar o jogo.\n");
            }
            else 
            {
              system("clear");
              printf("\n*---------------------------------------*");
              printf("\n*       Personagem [%d] Cadastrado.           ", iCPersona+1);  
              printf("\n*");         
              printf("\n*       Nome        : %s", lista_persona[iCPersona].sNm);
              printf("\n*       Raça        : %s", cMrc[lista_persona[iCPersona].iRc]); 
              printf("\n*       Alinhamento : %s", cMal[lista_persona[iCPersona].iAl]);
              printf("\n*       Profissão   : %s", cMpf[lista_persona[iCPersona].iPf]);
              printf("\n*       Meta        : %s", cMmt[lista_persona[iCPersona].iMt]);
              printf("\n*       Onde Vive   : %s", cMmv[lista_persona[iCPersona].iMv]);
              printf("\n*       Porte       : %s", cMpt[lista_persona[iCPersona].iPt]);
              printf("\n*");
              printf("\n*             Que os Jogos Começem             ");  
              printf("\n*                Boa Sorte!                    ");
              printf("\n*---------------------------------------*");
           }
          }
          else 
          {
            system("clear");
            printf("********              Cadastro Concluído                ********");
            do 
            {
              printf("\n 'Altere o Personagem'  ou ' Saia para iniciar o Jogo '\n\n");
              cMaOpcao=menu_persona();
              cVmaOpcao = valida_menu(cMaOpcao);
//
              switch (cVmaOpcao)
              {
                case '1':
                  iAPersona = 0;
                  iAltera =1;
                  break;      
                case '2':
                  iAPersona = 1;
                  iAltera =1;
                  break;      
                case '3':
                  iAPersona = 2;
                  iAltera =1;
                  break;
                case '9':
                  break;
                default:
                  system("clear");                  
                  printf("\n\nOpcao Invalida.");
                  printf("\n*---------------------------------------------------*");    
                  printf("\n    Por favor escolha uma das opções disponíveis.    ");      
                  printf("\n*---------------------------------------------------*");
                  break;
              }
            } while (cVmaOpcao != '9' && iAltera == 0); 
//
            if (cVmaOpcao == '9') 
            {
              printf("\n\nAlteração cancelado.\n");
            }
            else
            {
              cVmacp = cadastra_persona(iAPersona);
              iAltera = 0;
//
              if (cVmacp != 'S') 
              {
                printf("\nPersonagem continua com as mesmas caracteristicas anteriores.\n");
              }
              else 
              {
                system("clear");
                printf("\n*---------------------------------------*");
                printf("\n*       Personagem [%d] Alterado.           ", iAPersona+1);  
                printf("\n*");         
                printf("\n*       Nome        : %s", lista_persona[iAPersona].sNm);
                printf("\n*       Raça        : %s", cMrc[lista_persona[iAPersona].iRc]); 
                printf("\n*       Alinhamento : %s", cMal[lista_persona[iAPersona].iAl]);
                printf("\n*       Profissão   : %s", cMpf[lista_persona[iAPersona].iPf]);
                printf("\n*       Meta        : %s", cMmt[lista_persona[iAPersona].iMt]);
                printf("\n*       Onde Vive   : %s", cMmv[lista_persona[iAPersona].iMv]);
                printf("\n*       Porte       : %s", cMpt[lista_persona[iAPersona].iPt]);
                printf("\n*");
                printf("\n*             Que os Jogos Começem             ");  
                printf("\n*                Boa Sorte!                    ");
                printf("\n*---------------------------------------*");
              }
            }
          }
        }
        break;
      case '2':
        if (iTl_persona[0] == 0)
        {
          system("clear");
          printf("\n  Antes de iniciar o jogo é preciso 'Criar Personagem'. \n");
          printf("               Utilize a opcao '1' do Menu.               \n");
        }
        else 
        {
          cMaOpcao='0'; cVmaOpcao='0'; iPerJoga =0;
          system("clear");            
          printf("********              Vamos Jogar                ********");
          do 
          {
            printf("\n\n      'Escolha um personagem para começar o jogo.'    \n\n");
           
            cMaOpcao=menu_persona();
            cVmaOpcao = valida_menu_persona(cMaOpcao);
//
            switch (cVmaOpcao)
            {
              case '1':
                iAPersona = 0;
                iPerJoga =1;
                break;      
              case '2':
                iAPersona = 1;
                iPerJoga =1;
                break;      
              case '3':
                iAPersona = 2;
                iPerJoga =1;
                break;
              case '9':
                break;
              default:
                system("clear");                            
                printf("\n\nOpcao Invalida.");
                printf("\n*---------------------------------------------------*");
                printf("\n    Por favor escolha uma das opções disponíveis.   ");
                printf("\n*---------------------------------------------------*");
                break;
            }
          } while (cVmaOpcao != '9' && iPerJoga == 0); 
//
          if (cVmaOpcao == '9') 
          {
            printf("\n\nPartida cancelado.\n");
          }
          else
          {
            iCPclose=1;
            iEvtPersona=iAPersona;
            system("clear");
            printf("\n\n");
            printf("*---------------         Mensagem           ---------------*");
            printf("\n                  Prezado %s ", cMpf[lista_persona[iEvtPersona].iPf]);
            printf("%s\n", lista_persona[iEvtPersona].sNm);
            printf("*-----------------------------------------------------------*");
            for (iTcd1=0; iTcd1 < 17; iTcd1++)
            {
              printf("\n%s", cTcd1[iTcd1]);
            }
            printf("\n*-----------------------------------------------------------*\n");
            for (iTcd1=0; iTcd1 < 2; iTcd1++)
            {
              printf("%s\n", cTcd2[iTcd1]);
            }
            printf("*-----------------------------------------------------------*\n");

            indEvt = 1;
            cMevtOpcao = ' ';
            do 
            {
              printf(" Pressione Enter para continuar..."); 
              getchar();  // Pausa a execução e aguarda o pressionamento de Enter
              system("clear");              
              cMevtOpcao = menu_eventos(indEvt);
              if (cMevtOpcao == 'N')
              {
                printf("\n");
                printf("           Você parou no meio do Evento %d            \n",indEvt);
              }
              else if (cMevtOpcao == 'R')
              {
                if (indEvt == 3) 
                {
                  printf("\n      Sua ajuda foi muito importante mas        ");
                  printf("\n      agora você está sendo seguido,  por       ");
                  printf("\n      isso, volte e refaça seu caminho.         ");
                  printf("\n\n");                
                  indEvt = 2; 
                  cMevtOpcao = '0';                  
                } 
                else if (indEvt >= 4)
                {
                  printf("\n  Infelizmente você teve mais derrotas que vitórias \n");
                  cMevtOpcao = 'N';                    
                }
              }
              else  
              {
                indEvt ++; 
              }
            } while (cMevtOpcao != 'N' && indEvt <  6); 
//
            if (cMevtOpcao == 'N')
            {
              printf("\n*    Não foi desta vez que conseguiu chegar ao fim   *\n");
              printf("\n*              Mais sorte da próxima vez             *\n");
            }
            else 
            {
              system("clear");                            
              printf("\n                %s ", cMpf[lista_persona[iEvtPersona].iPf]);
              printf("%s \n", lista_persona[iEvtPersona].sNm);
              printf("*----------------------------------------------------*");
              printf("\n           Parabéns pela Vitória                  \n");
              printf("*----------------------------------------------------*"); 
              for (iTcd1=0; iTcd1 < 7; iTcd1++)
              {
                  printf("\n%s", cTev6[iTcd1]);
              }
            }
            if (indEvt >= 4) 
            { if (lista_persona[iEvtPersona].iVd < 100) 
              {
                lista_persona[iEvtPersona].iVd= 100;
                printf("\n*     Seus 100 Pontos de Vida foram restaurados      *");
              }
            }
                
              printf("\n*----------------------------------------------------*"); 
              printf("\n\n        Pressione Enter para continuar...    "); 
              getchar();  // Pausa a execução e aguarda o pressionamento de Enter
              system("clear");              
              
            
            
          }
        }
        break;
      case '3':
        printf("Até a próxima.");
        break;
      default:
        system("clear");
        printf("Opcao Invalida");
        break;
    }
  } while (cVOpcao != '3'); 
  
 return 0;
}
//
void inicializa_jogo(void)
{
  int i=0;
  
  for (i=0; i<TAM_persona;i++)
  {
    iTl_persona[i] = 0;    
  }
  for (i=0; i<TAM_charada;i++)
  {
    iTl_charada[i] = 0;
  }
}
//
char menu(void)
{
  char cFmOpcao;
  
  printf("\n******** Menu ********\n"); 
  printf("\nOpções:"); 
  printf("\n  1 - Criar Personagem."); //(Liberada ate comecar o jogo.)
  printf("\n  2 - Iniciar Jogo."); // (Bloqueada ate efetuar a opcao.)
  printf("\n  3 - Sair."); //(Só sai do jogo se digitar 3.)
  printf("\nDigite uma opcao: ");
  scanf(" %c%*[^\n]",&cFmOpcao);
  getchar();
  return cFmOpcao;
}
//
char valida_menu(char cFvmOpcao)
{
  if (isdigit(cFvmOpcao) == 0) 
  {
    return '%';
  }
  else
  {
    return cFvmOpcao;
  }
}
//
char menu_raca(void)
{
  char cFmrOpcao;
  
  printf("\nOpções:"); 
  printf("\n  1 - Humano. "); 
  printf("\n  2 - Anão. "); 
  printf("\n  3 - Elfo. "); 
  printf("\n  9 - Sair. "); 
  printf("\nDigite uma opcao: ");
  scanf(" %c%*[^\n]",&cFmrOpcao);
  getchar();
  return cFmrOpcao;
}
//
char menu_alinhamento(void)
{
  char cFmalOpcao;
  
  printf("\nOpções:"); 
  printf("\n  1 - Mal. "); 
  printf("\n  2 - Neutro. "); 
  printf("\n  3 - Bom. "); 
  printf("\n  9 - Sair. "); 
  printf("\nDigite uma opcao: ");
  scanf(" %c%*[^\n]",&cFmalOpcao);
  getchar();
  return cFmalOpcao;
}
//
char menu_profissao(int iAl)
{
  char cFmpfOpcao;
  
  printf("\nOpções:"); 
  printf("\n  1 - Guerreiro. "); 
  printf("\n  2 - Mago. ");
  if (iAl != 3) // Alinhamento "Bom" não pode ser Ladino
  {
    printf("\n  3 - Ladino. "); 
  }
  printf("\n  9 - Sair "); 
  printf("\nDigite uma opcao: ");
  scanf(" %c%*[^\n]",&cFmpfOpcao);
  getchar();
  return cFmpfOpcao;
}
//
char menu_meta(int iAl)
{
  char cFmmtOpcao;
  
  printf("\nOpções:"); 
  printf("\n  1 - Governar o reino. "); 
  printf("\n  2 - Ficar rico. ");
  if (iAl != 1) //Alinhamento "Mal" não pode destruir o mal
  {
    printf("\n  3 - Destruir o mal. "); 
  }
  printf("\n  9 - Sair. "); 
  printf("\nDigite uma opcao: ");
  scanf(" %c%*[^\n]",&cFmmtOpcao);
  getchar();
  return cFmmtOpcao;
}
//
char menu_meio(int iPf)
{
  char cFmmvOpcao;
  
  printf("\nOpções:"); 
  printf("\n  1 - Urbano. "); 
  printf("\n  2 - Rural. ");
  if (iPf != 3) //Profissão "Ladino" não pode ser tribal
  {
    printf("\n  3 - Tribal. "); 
  }
  printf("\n  9 - Sair "); 
  printf("\nDigite uma opcao: ");
  scanf(" %c%*[^\n]",&cFmmvOpcao);
  getchar();
  return cFmmvOpcao;
}
//
char menu_porte(int iRc)
{
  char cFmptOpcao;
  
  printf("\nOpções:"); 
  if (iRc != 2) //Raça "Anão" não pode ser grande
  {
    printf("\n  1 - Grande. ");   
  }
  printf("\n  2 - Médio. "); 
  printf("\n  3 - Pequeno. ");
  printf("\n  9 - Sair "); 
  printf("\nDigite uma opcao: ");
  scanf(" %c%*[^\n]",&cFmptOpcao);
  getchar();
  return cFmptOpcao;
}
//
int conta_persona() 
{
  int iCp=0;
  for (iCp=0; iCp < TAM_persona; iCp++)
  {
    if (iTl_persona[iCp] == 0)
    {
      break;
    }
  }
  return iCp;
}
//
char menu_persona(void)
{
  int ima=0, iFmpersona=0;
  char cFmaOpcao;

  iFmpersona=conta_persona();  

  for (ima=0; ima < iFmpersona; ima++) 
  {        
    printf("%d - Nome: %s ", ima+1, lista_persona[ima].sNm);
    printf("\n    Caracteristicas:");
    printf("\n    Raça: %s ", cMrc[lista_persona[ima].iRc]); 
    printf("- Alinhamento: %s ", cMal[lista_persona[ima].iAl]);
    printf("- Profissão: %s ", cMpf[lista_persona[ima].iPf]);
    printf("\n    Meta: %s ", cMmt[lista_persona[ima].iMt]);
    printf("- Onde vive: %s ", cMmv[lista_persona[ima].iMv]);
    printf("- Porte: %s ", cMpt[lista_persona[ima].iPt]);
    printf("\n");
  }
//  
  printf("\nEscolha um personagem.\n");
    
  for (ima=0; ima < iFmpersona; ima++)
  {
    printf("\n  %d - %s", ima+1, lista_persona[ima].sNm);
  }
//  
  printf("\n  9 - Sair. ");
  printf("\nDigite uma opcao: ");
  scanf(" %c%*[^\n]",&cFmaOpcao);
  getchar();
//
  if (isdigit(cFmaOpcao) != 0 )
  {
    if ((cFmaOpcao != '9') && ((cFmaOpcao - 48) > iFmpersona))
    {
//
      return '&';
    }
    else
    {
      return cFmaOpcao;  
    }
  }
  else
  {
    return cFmaOpcao;  
  }
}
//
char valida_menu_persona(char cFvmpOpcao)
{
  int iCvmp=0;

  iCvmp=conta_persona();

  if (isdigit(cFvmpOpcao) != 0 )
  {
    if ((cFvmpOpcao != '9') && ((cFvmpOpcao - 48) > iCvmp)) 
    {
      return '&';
    }
    else
    {
      return cFvmpOpcao;  
    }
  }
  else
  {
    return cFvmpOpcao;  
  }
}
//
char cadastra_persona(int iCcpersona)
{
  int iFcp=0, jFcp=0, iRc=0, iAl=0, iPf=0, iMt=0, iMv=0, iPt=0, iVd=0; 
  char sFcpNome[21], cFcpLetra, cFmrOpcao, cFvmrOpcao, cFcpInv='0', cFalOpcao, cFvalOpcao, 
  cFpfOpcao, cFvpfOpcao, cFmtOpcao, cFvmtOpcao, cFmvOpcao,   cFvmvOpcao, cFptOpcao, 
  cFvptOpcao;

  system("clear");
  printf("\nEscolha como você sera chamado. Max:20 Caracteres.\n");
  printf("Digite o nome da sua personagem [%d]: ", iCcpersona+1);
  for(iFcp=0;cFcpLetra != '\n';iFcp++) 
  {
    cFcpLetra=getchar();
    sFcpNome[iFcp]=cFcpLetra;
    if (iFcp > 21)
    {
      break;
    }
  }  
//  
  iFcp--;
  sFcpNome[iFcp]='\0';//o índice atual do vetor de caracteres recebe a terminação da string
  
  if (iFcp > 20)
  {
    system("clear");
    printf("\nNome ultrapassou ao máximo de caracteres permitido.\n");
    cFcpInv='1';
  }
  else if (sFcpNome[0]=='\0') 
  {
    system("clear");
    printf("\nDigite um nome válido. Não identiticamos caracteres válidos.\n");
    cFcpInv='1';
  }
  else 
  {
    for (jFcp=0; jFcp<iFcp; jFcp++)
    {
      if (((isalpha(sFcpNome[jFcp]) == 0) && (isdigit(sFcpNome[jFcp]) == 0 )) || (sFcpNome[jFcp] == 32))
      {
        if (cFcpInv == '0')
        {
          system("clear");
          printf("\nNome '%s' com caracteres inválidos.\n", sFcpNome);
          printf("Favor usar apenas letras e numeros.\n");
        }
        cFcpInv='1';
        printf("Caracter inválido: '%c'\n",sFcpNome[jFcp]);
      }    
    }  
  }
//
  if (cFcpInv == '1' ) 
  {
    return 'N';
  }
  else 
  {
    system("clear");
    printf("\nMuito bem  %s! ", sFcpNome);
    printf("\nAgora vamos ver as raças disponíveis.");

    do 
    {
      printf("\n");
      cFmrOpcao = menu_raca();
      cFvmrOpcao = valida_menu(cFmrOpcao);
//
      switch (cFvmrOpcao)
      {
        case '1':
          iRc = 1;
          break;      
        case '2':
          iRc = 2;
          break;      
        case '3':
          iRc = 3;
          break;
        case '9':
          break;
        default:
          system("clear");
          printf("\nOpcao Invalida.");
          printf("\n*---------------------------------------------------*");          
          printf("\n %s! Por favor escolha uma das opções disponíveis.", sFcpNome); 
          printf("\n               As raças disponíveis         ");
          printf("\n*---------------------------------------------------*");
      }
    } while (cFvmrOpcao != '9' && iRc == 0); 
//
    if (cFvmrOpcao == '9') 
    {
      printf("\n\nCadastramento cancelado.");
      printf("\nRaca não foi selecionada.\n");
      return 'R';
    }
    else 
    {
      system("clear");
      printf("Boa escolha %s!", sFcpNome);
      printf("\nVejamos os alinhamentos disponíveis.");

      do 
      {
        printf("\n");
        cFalOpcao = menu_alinhamento();
        cFvalOpcao = valida_menu(cFalOpcao);
//
        switch (cFvalOpcao)
        {
          case '1':
            iAl = 1;
            break;      
          case '2':
            iAl = 2;
            break;      
          case '3':
            iAl = 3;
            break;
          case '9':
            break;
          default:
          system("clear");
          printf("\nOpcao Invalida.");
          printf("\n*---------------------------------------------------*");          
          printf("\n %s! Por favor escolha uma das opções disponíveis. ", sFcpNome);
          printf("\n             Alinhamentos disponíveis      ");
          printf("\n*---------------------------------------------------*");
        }
      } while (cFvalOpcao != '9' && iAl == 0); 
//
      if (cFvalOpcao == '9') 
      {
        printf("\n\nCadastramento cancelado.");
        printf("\nAlinhamento não foi selecionada.");
        return 'A';
      }
      else
      { 
        system("clear");
        printf("%s! Você precisa de uma profissão.", sFcpNome);
        printf("\n\nVamos ver as disponíveis.");
        
        do 
        {
          printf("\n");
          cFpfOpcao = menu_profissao(iAl);
          cFvpfOpcao = valida_menu(cFpfOpcao);
//
          if (iAl == 3 && cFvpfOpcao == '3')
          {
            cFvpfOpcao = '%';
          }
          switch (cFvpfOpcao)
          {
            case '1':
              iPf = 1;
              break;      
            case '2':
              iPf = 2;
              break;      
            case '3':
              iPf = 3;
              break;
            case '9':
              break;
            default:
              system("clear");
              printf("\nOpcao Invalida.");
              printf("\n*---------------------------------------------------*");          
              printf("\n %s! Por favor escolha uma das opções disponíveis.", sFcpNome);
              printf("\n             Profissoes disponíveis         ");
              printf("\n*---------------------------------------------------*");
          }
        } while (cFvpfOpcao != '9' && iPf == 0); 
//
        if (cFvpfOpcao == '9') 
        {
          printf("\n\nCadastramento cancelado.");
          printf("\nProfissão não foi selecionada.\n");
          return 'P';
        }
        else 
        {
          system("clear");
          printf("%s! Você precisa traçar uma meta.", sFcpNome);
          printf("\n\nVamos ver as disponíveis.");
//        
          do 
          {
            printf("\n");
            cFmtOpcao = menu_meta(iAl);
            cFvmtOpcao = valida_menu(cFmtOpcao);
//
            if (iAl == 1 && cFvmtOpcao == '3')
            {
              cFvmtOpcao = '%';
            }
            switch (cFvmtOpcao)
            {
              case '1':
                iMt = 1;
                break;      
              case '2':
                iMt = 2;
                break;      
              case '3':
                iMt = 3;
                break;
              case '9':
                break;
              default:
                system("clear");
                printf("\nOpcao Invalida.");
                printf("\n*---------------------------------------------------*");          
                printf("\n %s! Por favor escolha uma das opções disponíveis.", sFcpNome);
                printf("\n                Metas disponíveis      ");
                printf("\n*---------------------------------------------------*");
            }
          } while (cFvmtOpcao != '9' && iMt == 0); 

          if (cFvmtOpcao == '9') 
          {
            printf("\n\nCadastramento cancelado.");
            printf("\nMeta não foi estabelecida.\n");
           return 'M';   
          }            
          else
          {
            system("clear");
            printf("%s! Onde você vive?", sFcpNome);
            printf("\n\nMarque uma das disponíveis.");
      
            do 
            {
              printf("\n");
              cFmvOpcao = menu_meio(iPf);
              cFvmvOpcao = valida_menu(cFmvOpcao);
//
              if (iPf == 3 && cFvmvOpcao == '3')
              {
                cFvmvOpcao = '%';
              }
              switch (cFvmvOpcao)
              {
                case '1':
                  iMv = 1;
                  break;      
                case '2':
                  iMv = 2;
                  break;      
                case '3':
                  iMv = 3;
                  break;
                case '9':
                  break;
                default:
                  system("clear");
                  printf("\nOpcao Invalida.");
                  printf("\n*---------------------------------------------------*");       
                  printf("\n %s! Por favor escolha uma das opções disponíveis.", sFcpNome); 
                  printf("\n           Meios de Vida disponíveis      ");
                  printf("\n*---------------------------------------------------*");
              }
            } while (cFvmvOpcao != '9' && iMv == 0); 

            if (cFvmvOpcao == '9') 
            {
              printf("\n\nCadastramento cancelado.");
              printf("\nMeio onde vive não foi estabelecida.\n");
              return 'V';
            }
            else
            {
              system("clear");
              printf("%s! Qual o seu Porte?", sFcpNome);
              printf("\n\nVeja as classificações disponíveis.");
              do 
              {
                printf("\n");
                cFptOpcao = menu_porte(iRc);
                cFvptOpcao = valida_menu(cFptOpcao);
//
                if (iRc == 2 && cFvptOpcao == '1')
                {
                  cFvptOpcao = '%';
                }
                switch (cFvptOpcao)
                {
                  case '1':
                    iPt = 1;
                    break;      
                  case '2':
                    iPt = 2;
                     break;      
                  case '3':
                    iPt = 3;
                    break;
                  case '9':
                    break;
                  default:
                    system("clear");
                    printf("\nOpcao Invalida.");
                    printf("\n*---------------------------------------------------*");
                    printf("\n% s! Por favor escolha uma das opções disponíveis.", sFcpNome);
                    printf("\n             Portes disponíveis           ");           
                    printf("\n*---------------------------------------------------*");
                }
              } while (cFvptOpcao != '9' && iPt == 0); 

              if (cFvptOpcao == '9') 
              {
                printf("\n\nCadastramento cancelado.");
                printf("\nPorte não foi estabelecida.\n");
                return 'P';
              }  
              else
              {
                strcpy(lista_persona[iCcpersona].sNm, sFcpNome);
                lista_persona[iCcpersona].iRc = iRc-1;
                lista_persona[iCcpersona].iAl = iAl-1;
                lista_persona[iCcpersona].iPf = iPf-1;
                lista_persona[iCcpersona].iMt = iMt-1;
                lista_persona[iCcpersona].iMv = iMv-1;
                lista_persona[iCcpersona].iPt = iPt-1;
                iVd=100;
                lista_persona[iCcpersona].iVd = iVd;
                iTl_persona[iCcpersona] = 1;
                return 'S';
              }
            }      
          }
        }
      }
    }
  }
}

char menu_eventos(int iEvt)
{
  char cFmevtOpcao='0', cFvevtOpcao='0', cFmevtJj='0', cFmevtlc='0';
  int iFevt=0, iEvento=0, iFmevtAl, iFmevtPf, iFmevtVd;
//
  switch (iEvt) 
  {
    case 1:
      printf("\n");
      printf("*             O Desafio do Templo Assombrado                *\n");
      printf("*-----------------------------------------------------------*");
      for (iFevt=0; iFevt < 9; iFevt++)
      {
        printf("\n%s", cTev1[iFevt]);
      }
      printf("\n*-----------------------------------------------------------*\n");
      break;
    case 2:
      printf("\n");
      printf("*            A Conspiração Real                *\n");
      printf("*----------------------------------------------*");
      for (iFevt=0; iFevt < 8; iFevt++)
      {
        printf("\n%s", cTev2[iFevt]);
      }
      printf("\n*----------------------------------------------*\n");
      break;
    case 3:
      printf("\n");
      printf("*              A Descoberta                    *\n");
      printf("*------------------------------------------------*");
      for (iFevt=0; iFevt < 6; iFevt++)
      {
        printf("\n%s", cTev3[iFevt]);
      }
      printf("\n*----------------------------------------------*\n");
      break;
    case 4:
      printf("\n");
      printf("*         Jokenpô contra o Rei Furioso            *\n");
      printf("*-------------------------------------------------*");
      for (iFevt=0; iFevt < 4; iFevt++)
      {
        printf("\n%s", cTev4[iFevt]);
      }
       printf("\n*-------------------------------------------------*\n");
      break;
    case 5:
      printf("\n");
      printf("*         Clímax: Batalha das Charadas         *\n");
      printf("*----------------------------------------------*");
      for (iFevt=0; iFevt < 5; iFevt++)
      {
        printf("\n%s", cTev5[iFevt]);
      }
      printf("\n*----------------------------------------------*\n");
      break;    
    default:
      printf("Evento %d em contrução", iEvt);
  }
//
  do 
  {
    cFmevtOpcao=lista_evento(iEvt);
    cFvevtOpcao = valida_menu(cFmevtOpcao);    
//
    if (iEvt == 1 )
    {
      system("clear");   
      printf("\n");
      printf("*      O Desafio do Templo Assombrado          *\n");
      printf("*----------------------------------------------*\n");
    } 
    else if (iEvt == 2 )
    {
      system("clear");   
      printf("\n");
      printf("*            A Conspiração Real                *\n");
      printf("*----------------------------------------------*\n");
//
      iFmevtAl = lista_persona[iEvtPersona].iAl;

      if  ((cFvevtOpcao == '2' && iFmevtAl == 2 ) ||  
           (cFvevtOpcao == '3' && iFmevtAl == 0 ) )
      {
        cFvevtOpcao = '&';
      }
    }
    else if (iEvt == 3 )
    {
      system("clear");   
      printf("\n");
      printf("*               A Descoberta                  *\n");
      //
      iFmevtPf = lista_persona[iEvtPersona].iPf;

      if (cFvevtOpcao == '3')
      {
        cFvevtOpcao = '&';
      }
    }
    else 
    {
      if ((cFvevtOpcao == '2') || (cFvevtOpcao == '3'))
      {
        cFvevtOpcao = '&';
      }
    }
//    
    switch (cFvevtOpcao)
    {
      case '1':
        if (iEvt==1)
        {
          printf("              Teste do atleta                   \n");
          printf("*----------------------------------------------*\n");
          printf("    Nesse caminho  você enfrentará escaladas    \n");
          printf("    e criaturas selvagens. Somente coragem e    \n");
          printf("    destreza o levarão ao coração do templo.    \n");
          printf("*----------------------------------------------*\n");
          iEvento=1;
        } 
        else if (iEvt==2)
        {
          printf("              Fuga pelas Sombras                \n");
          printf("*----------------------------------------------*\n");
          printf("      Você decide utilizar suas habilidades     \n"); 
          printf("      furtivas  e  conhecimento do  castelo     \n"); 
          printf("      para escapar despercebido.                \n"); 
          printf("      Você deve se infiltrar  nas  sombras,     \n"); 
          printf("      evitar  guardas  e  encontrar  rotas      \n"); 
          printf("      secretas para escapar do castelo com      \n"); 
          printf("      o Elixir.                                 \n");
          printf("      Cada passo é perigoso, mas se você for    \n");
          printf("      astuto o suficiente, conseguirá escapar   \n"); 
          printf("      sem que o Rei saiba.                      \n");
          printf("      (Decidindo pela fuga pelas sombras, se    \n");
          printf("      torna um verdadeiro mestre do sigilo e    \n");
          printf("      da dissimulação.                          \n");
          printf("      Com movimentos rápidos e silenciosos,     \n");
          printf("      você evita os guardas e alquimistas       \n");
          printf("      traidores enquanto se movimenta pelo      \n");
          printf("      castelo real, levando consigo o Elixir    \n");
          printf("      da Vida.)                                 \n");
          printf("*----------------------------------------------*\n");
           iEvento=1;
        }
        else if (iEvt==3)
        {
          printf("*---------------------------------------------*\n"); 
          printf("    Despistar os extraterrestres e salvar seu  \n");
          printf("    amigo dragão com o elixir da vida.         \n");
          printf("*---------------------------------------------*\n");
           iEvento=2;
        }
        else if (iEvt==4)
        {
          cFmevtJj=jogar_jokenpo();
//        
          if (cFmevtJj == 'N' )
          {
            cFvevtOpcao = '9';
          } 
          else if (cFmevtJj == 'R')
          {
            iEvento = 2;  
          } 
          else if (cFmevtJj == 'S')
          {
            iEvento = 1;  
          }
        }
        else if (iEvt==5)
        {
          cFmevtlc=lista_charadas();
          if (cFmevtlc == 'N' )
          {
            cFvevtOpcao = '9';
          } 
          else if (cFmevtlc == 'R')
          {
            iEvento = 2;  
          } 
          else if (cFmevtlc == 'S')
          {
            iEvento = 1;  
          }
        }  
        break;
      case '2':
        if (iEvt==1)
        {
          printf("              Teste do nerd                     \n");
          printf("*----------------------------------------------*\n");          
          printf("   Nesse caminho você resolverá códigos  e      \n");
          printf("   quebra-cabeças. Desvendar os segredos do     \n");          
          printf("   templo o levarão a câmara principal.         \n");
          printf("*----------------------------------------------*\n");
        }
        else if (iEvt==2)
        {
          printf("               Batalha Épica                    \n");
          printf("*----------------------------------------------*\n");
          printf("  Sentindo-se confiante em suas habilidades de  \n");
          printf("  combate, você decide matar  a família  do Rei \n");
          printf("  e seus ajudantes. Em uma batalha épica,  você \n");
          printf("  luta com coragem e mata muitos. Utilize suas  \n");
          printf("  armas, magias e  estratégias  para  derrotar  \n");
          printf("  seus adversários e manter o elixir seguro.    \n");
          printf("  (Em meio a uma batalha furiosa, você enfrenta \n");
          printf("  os adversários um a um, utilizando suas       \n");
          printf("  técnicas de combate e magias poderosas para   \n");
          printf("  defender o Elixir a todo custo.               \n");
          printf("  Cada golpe certeiro e feitiço lançado reforça \n"); 
          printf("  a sua determinação em proteger o segredo da   \n");
          printf("  imortalidade.)                                \n");
          printf("*----------------------------------------------*\n");          
        }
        else if (iEvt==3) 
        {
          if (iFmevtPf == 0)
          {
            printf("*---------------------------------------------*\n");                    
            printf("   Como um guerreiro habilidoso, você decide   \n");
            printf("   enfrentar as criaturas de frente, confiando \n");
            printf("   em sua força e habilidades de combate corpo \n");
            printf("   a corpo. Empunhando sua espada afiada e     \n");
            printf("   usando sua armadura resistente, você avança \n");
            printf("   corajosamente em direção às criaturas,      \n");
            printf("   enfrentando-os em um combate feroz.         \n");
            printf("*---------------------------------------------*\n");            
          } 
          else if (iFmevtPf == 1) 
          {
            printf("*---------------------------------------------*\n");
            printf(" Como um mago poderoso, você prefere usar      \n");
            printf(" suas habilidades mágicas para enfrentar       \n");
            printf(" as criaturas. Concentrando-se na manipulação  \n"); 
            printf(" dos elementos, você conjura chamas ardentes e \n"); 
            printf(" relâmpagos devastadores.                      \n");  
            printf("*---------------------------------------------*\n");  
          }
          else if (iFmevtPf == 2) 
          {
            printf("*---------------------------------------------*\n");            
            printf("     Como um ladino astuto, você prefere       \n");
            printf("     abordar a situação com furtividade e      \n");
            printf("     agilidade. Utilizando suas habilidades    \n");
            printf("     de movimento silencioso e furtividade,    \n");
            printf("     você evita as sentinelas criaturas e      \n");
            printf("     procura eliminar os inimigos um a um,     \n");
            printf("     sem ser detectado.                        \n");
            printf("*---------------------------------------------*\n");            
          }
          else 
          {
            printf(" Cuidado! Algo ocorreu de estranho, Não temos mensagem para você.");
          }
        }
        iEvento=1;
        break;      
      case '3':
        if (iEvt==1)
        {
          printf("             Teste do alquimista                \n");
          printf("*----------------------------------------------*\n");
          printf("     Nesse caminho você precisará manipular e   \n");
          printf("     combinar várias substâncias místicas que   \n");          
          printf("     levarão ao centro do templo.               \n");
          printf("*----------------------------------------------*\n");                    
        }
        else if (iEvt==2)
        {
          printf("           Aliança Surpreendente                \n");
          printf("*----------------------------------------------*\n");
          printf("  Consciente de que a luta  será difícil, você  \n"); 
          printf("  decide procurar ajuda  inesperada.  Buscando  \n");
          printf("  um traidor leal ao  Rei que  deseje  expor a  \n");
          printf("  conspiração,você forma uma aliança inusitada  \n");
          printf("   para garantir a segurança do Elixir.         \n");
          printf("  Juntos,  vocês  planejam  uma emboscada para  \n"); 
          printf("  capturar os conspiradores e revelar a traição \n");
          printf("  ao reino.                                     \n");
          printf("*----------------------------------------------*\n");
        }        
        iEvento=1;
        break;
      case '9':
        break;
      default:
        printf("\n\nOpcao Invalida.");
        printf("\n*---------------------------------------------------*");          
        printf("\n  Por favor escolha uma das opções disponíveis.      ");      
        printf("\n*---------------------------------------------------*");
        break;
    }
  } while (cFvevtOpcao != '9' && iEvento == 0); 
//    
 if (cFvevtOpcao == '9') 
 {
    return 'N';
 }
 else
 {
   if (iEvento == 1)
   {
     return 'S';  
   }
   else
   {
     return 'R';
   }
 }
}
//  
char lista_evento (int iFevt)
{
  char cFlevtOpcao=0;
  int iLevtAl, ilmevtPf;

  iLevtAl = lista_persona[iEvtPersona].iAl;
  ilmevtPf = lista_persona[iEvtPersona].iPf;
  
  printf("\nOpções:\n"); 
  switch (iFevt)    
  {
    case 1:
      printf("\n  1 - Teste do atleta"); 
      printf("\n  2 - Teste do nerd");
      printf("\n  3 - Teste do alquimista");
      break;
    case 2:
      printf("\n  1 - Fuga pelas Sombras");   
      if (iLevtAl != 2) 
      {
        printf("\n  2 - Batalha Épica");  
      }
      if (iLevtAl != 0) 
      {
        printf("\n  3 - Aliança Surpreendente");  
      }
      
      break;    
    case 3:
      printf("\n  1 - Salvar um amigo");
      if (ilmevtPf == 0)
      {
        printf("\n  2 - Enfrentar seus inimigos");    
      } 
      else if (ilmevtPf == 1)
      {
        printf("\n  2 - Concentre-se em manipular os elementos");  
      } 
      else if (ilmevtPf == 2)
      {
        printf("\n  2 - Despiste as sentinelas");  
      } 
      else
      {
        printf("\n  x - Opção desativada");
      }
      break;    
    case 4:
      printf("\n  1 - Joga Jokenpô");
      break;    
    case 5:
      printf("\n  1 - Batalha das Charadas");
      break;    
    default:
      printf("\nEvento [%d] sem opções disponíveis", iFevt);
  }

  printf("\n  9 - Sair "); 
  printf("\n\nDigite uma opcao: ");
  scanf(" %c%*[^\n]",&cFlevtOpcao);
  getchar();
  return cFlevtOpcao;
}
//
char jogar_jokenpo()
{
  int iFjj=0, iFjjVt=0, iFjjConv=0, iFvjjOpcao=0, iFjjCalc=0, iFevtVd=0;
  char cFjjOpcao, cFvjjOpcao;

  iFevtVd = lista_persona[iEvtPersona].iVd;
  printf("\n");
  printf("*-------------------------------------------------*");
  for (iFjj=0; iFjj < 4; iFjj++)
  {
    printf("\n%s", cTev41[iFjj]);
  }
  printf("\n*-------------------------------------------------*\n");

  do
  {
    printf("\n Pressione Enter para continuar..."); 
    getchar();  // Pausa a execução e aguarda o pressionamento de Enter
    system("clear");
    do
    {      
      printf("\n*           Jokenpô contra o Rei Furioso          *");
      printf("\n*-------------------------------------------------*");
      printf("\n               %s %s, não desista. ",cMpf[lista_persona[iEvtPersona].iPf], lista_persona[iEvtPersona].sNm);
      printf("\n       Tenha determinação para chegar ao final");
      printf("\n            Seus pontos de vida atual: %d\n", iFevtVd);    
      printf("\n  Escolha:   ");
      printf("\n     1 - Pedra   ");
      printf("\n     2 - Papel   ");
      printf("\n     3 - Tesoura ");
      printf("\n     9 - Sair    ");
      printf("\n  Digite uma opcao: ");
      scanf(" %c%*[^\n]",&cFjjOpcao);
      getchar();
      cFvjjOpcao=valida_menu(cFjjOpcao);
//
    
      switch (cFvjjOpcao)
      {
        case '1':
          iFvjjOpcao = 1;
          iFjjConv =1;
          break;      
        case '2':
          iFvjjOpcao = 2;
          iFjjConv =1;
          break;      
        case '3':
          iFvjjOpcao = 3;
          iFjjConv =1;
          break;
        case '9':
          break;
        default:
          system("clear");                  
          printf("\n\nOpcao Invalida.");
          printf("\n*---------------------------------------------------*");    
          printf("\n    Por favor escolha uma das opções disponíveis.    ");      
          printf("\n*---------------------------------------------------*\n\n");
          iFjjConv =0;
          break;
      }      
    } while (cFvjjOpcao != '9' && iFjjConv == 0);  
//
    if (cFvjjOpcao != '9') 
    {
      int rand();
      iFjjCalc = rand() % 3+1; 
//    
      if ((iFvjjOpcao == 1 && iFjjCalc == 3) || 
          (iFvjjOpcao == 2 && iFjjCalc == 1) || 
          (iFvjjOpcao == 3 && iFjjCalc == 2)) 
      {
        printf("\n                 Você ganhou!                    \n");
        iFjjVt++;
      } 
      else if (iFvjjOpcao == iFjjCalc) 
      {
        printf("\n                    Empate!                        \n");
      } 
      else 
      {
        printf("\n                    Você perdeu!                   \n");
        iFevtVd -= 10;
      }      
    }
  } while (iFjjVt < 2 && iFevtVd > 0 && cFvjjOpcao != '9');
  
  if (cFvjjOpcao == '9') 
  {
    return 'N';
  }
  else
  {
    if (iFevtVd <= 0) 
    {
      return 'R';
    } 
    else 
    {
      lista_persona[iEvtPersona].iVd= iFevtVd;
      return 'S';
    } 
  } 
}
//
char lista_charadas()
{
  int iFlcCalc=0, iFlcAcha=0, iFlc=0, iFvlcOpcao=0, iFlcConv=0, iFlcVt=0, iFlctVd=0;
  char cFlcOpcao='0', cFvlcOpcao='0';

  iFlctVd = lista_persona[iEvtPersona].iVd;
  
  printf("\n*----------------------------------------------*");
  printf("\n*      Leia com atenção antes de responder     *");
  printf("\n*   Precisa acertar '3' Charadas para vencer   *");
  printf("\n*----------------------------------------------*");
  
  do
  {
    printf("\n Pressione Enter para continuar..."); 
    getchar();  // Pausa a execução e aguarda o pressionamento de Enter
    system("clear");
  
    do 
    {
      iFlcCalc = rand() % 10; 
      if (iTl_charada[iFlcCalc] == 0)
      {
        iFlcAcha = 1;
      }      
    } while (iFlcAcha == 0);
    iTl_charada[iFlcCalc] = 1;
    iFlcAcha = 0;
    do
    {
      printf("\n");
      printf("*------------------------------------------------------------------*\n");
      printf("                   Clímax: Batalha das Charadas                 \n");
      printf("                         Charada  %d                         \n",iFlcCalc+1);
      printf("                   Seus pontos de vida atual: %d             \n", iFlctVd);
      printf("*------------------------------------------------------------------*\n\n");
      printf (" %s ", cTev6C1[iFlcCalc]);
      printf("\n");
      printf ("%s ", cTev6Op[iFlcCalc]);
      printf("   9 - Sair    ");
      printf("\n  Informe a resposta correta: ");
      scanf(" %c%*[^\n]",&cFlcOpcao);
      getchar();
      cFvlcOpcao=valida_menu(cFlcOpcao);
//
      switch (cFvlcOpcao)
      {
        case '1':
          iFvlcOpcao = 1;
          iFlcConv   = 1;
          break;      
        case '2':
          iFvlcOpcao = 2;
          iFlcConv   =1;
          break;      
        case '3':
          iFvlcOpcao = 3;
          iFlcConv   =1;
          break;
        case '9':
          break;
        default:
          system("clear");                  
          printf("\n\nOpcao Invalida.");
          printf("\n*---------------------------------------------------*");    
          printf("\n    Por favor escolha uma das opções disponíveis.    ");      
          printf("\n*---------------------------------------------------*\n\n");
          iFlcConv =0;
          break;
      }      
    } while (cFvlcOpcao != '9' && iFlcConv == 0);  
//
    if (cFvlcOpcao != '9') 
    {
      if (iFvlcOpcao == cTev6Resp[iFlcCalc])  
      {
        printf("\n                 Você Acertou!                    \n");
        iFlcVt++;
      }
      else 
      {
        printf("\n                 Você Errou!                   \n");
        iFlctVd -= 50;
      }
      iFlcConv = 0;
    }
  } while (iFlcVt < 3 && iFlctVd > 0 && cFvlcOpcao != '9');
  
  if (cFvlcOpcao == '9') 
  {
    return 'N';
  }
  else
  {
    if (iFlctVd <= 0) 
    {
      return 'R';
    } 
    else 
    {
      lista_persona[iEvtPersona].iVd = iFlctVd;
      return 'S';
    } 
  } 
}
