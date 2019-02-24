#include <stdio.h>
#include "calc3.h"
#include "y.tab.h"

static int lbl;

int ex(nodeType *p) {
    int lbl1, lbl2;

    if (!p) return 0;
    switch(p->type) {
    case typeCon:       
        printf("\tpush\t%d\n", p->con.value); 
        break;
    case typeId:        
	printf("\tmov\t%d,rax\n", p->id.i);
        printf("\tpush\tsymtab(,rax,8)\n");
        break;
    case typeOpr:
        switch(p->opr.oper) {
        case WHILE:
            printf("L%03d:\n", lbl1 = lbl++);
            ex(p->opr.op[0]);
            // printf("\tjz\tL%03d\n", lbl2 = lbl++);
	    lbl2 = lbl++;
            ex(p->opr.op[1]);
            printf("\tjmp\tL%03d\n", lbl1);
            printf("L%03d:\n", lbl2);
            break;
        case IF:
            ex(p->opr.op[0]);
            if (p->opr.nops > 2) {
                /* if else */
                // printf("\tjz\tL%03d\n", lbl1 = lbl++);
		lbl1 = lbl++;
                ex(p->opr.op[1]);
                printf("\tjmp\tL%03d\n", lbl2 = lbl++);
                printf("L%03d:\n", lbl1);
                ex(p->opr.op[2]);
                printf("L%03d:\n", lbl2);
            } else {
                /* if */
                // printf("\tjz\tL%03d\n", lbl1 = lbl++);
		lbl1 = lbl++;
                ex(p->opr.op[1]);
                printf("L%03d:\n", lbl1);
            }
            break;
        case PRINT:     
            ex(p->opr.op[0]);
            // printf("\tprint\n");
	    printf("\tpop\trdx\n");
	    printf("\tcall\tprint\n");
            break;
        case '=':       
            ex(p->opr.op[1]);
	    printf("\tmov\t%d,rax\n", p->opr.op[0]->id.i);
            printf("\tpop\tsymtab(,rax,8)\n");
            break;
        case UMINUS:    
            ex(p->opr.op[0]);
            printf("\tneg\n");
            break;
	case FACT:
  	    ex(p->opr.op[0]);
	    printf("\tfact\n");
	    break;
	case LNTWO:
	    ex(p->opr.op[0]);
	    printf("\tlntwo\n");
	    break;
        default:
            ex(p->opr.op[0]);
            ex(p->opr.op[1]);
            switch(p->opr.oper) {
	    case GCD:   printf("\tpop\trdx\n"); printf("\tpop\trsx\n"); printf("\tcall\tgcd\n"); break;
            case '+':   printf("\tpop\trax\n"); printf("\tpop\trdx\n"); printf("\tadd\trax,rdx\n"); break;
            case '-':   printf("\tpop\trax\n"); printf("\tpop\trdx\n"); printf("\tsub\trax,rdx\n"); break;
            case '*':   printf("\tpop\trax\n"); printf("\tpop\trdx\n"); printf("\tmul\trdx\n"); break;
            case '/':   printf("\tpop\trax\n"); printf("\tpop\trdx\n"); printf("\tmov\tRBX,0\n"); printf("\tdiv\trdx,0\n"); break;
            case '<':   printf("\tpop\trax\n"); printf("\tpop\trdx\n"); printf("\tcmp\trax,rdx\n"); printf("\tjl\tL%03d\n", lbl); break;
            case '>':   printf("\tpop\trax\n"); printf("\tpop\trdx\n"); printf("\tcmp\trax,rdx\n"); printf("\tjg\tL%03d\n", lbl); break; 
            case GE:    printf("\tpop\trax\n"); printf("\tpop\trdx\n"); printf("\tcmp\trax,rdx\n"); printf("\tjge\tL%03d\n", lbl); break;
            case LE:    printf("\tpop\trax\n"); printf("\tpop\trdx\n"); printf("\tcmp\trax,rdx\n"); printf("\tjle\tL%03d\n", lbl); break;
            case NE:    printf("\tpop\trax\n"); printf("\tpop\trdx\n"); printf("\tcmp\trax,rdx\n"); printf("\tjne\tL%03d\n", lbl); break;
            case EQ:    printf("\tpop\trax\n"); printf("\tpop\trdx\n"); printf("\tcmp\trax,rdx\n"); printf("\tje\tL%03d\n", lbl); break;
            }
        }
    }
    return 0;
}
