/*
 *
 * The macro.c file is part of the restored ZAS.COM program
 * from the Hi-Tech C compiler v3.09
 *
 * Not a commercial goal of this laborious work is to popularize among
 * potential fans of 8-bit computers the old HI-TECH C compiler V3.09
 * (HI-TECH Software) and extend its life, outside of the CP/M environment
 * (Digital Research, Inc), for full operation in a  Unix-like operating
 * system UZI-180 without using the CP/M emulator.
 *
 * The HI-TECH C compiler V3.09 is provided free of charge for any use,
 * private or commercial, strictly as-is. No warranty or product support
 * is offered or implied including merchantability, fitness for a particular
 * purpose, or non-infringement. In no event will HI-TECH Software or its
 * corporate affiliates be liable for any direct or indirect damages.
 *
 * You may use this software for whatever you like, providing you acknowledge
 * that the copyright to this software remains with HI-TECH Software and its
 * corporate affiliates.
 *
 * All copyrights to the algorithms used, binary code, trademarks, etc.
 * belong to the legal owner - Microchip Technology Inc. and its subsidiaries.
 * Commercial use and distribution of recreated source codes without permission
 * from the copyright holderis strictly prohibited.
 *
 * Early work on the decompilation was done by Andrey Nikitin
 * Completion of the work and porting to work under modern compilers done by Mark Ogden
 * 22-May-2022
 */
#include "zas.h"

/**************************************************************************
 56 2c1b +++
 **************************************************************************/
void parseParamAndBody(register sym_t *ps) {
    sym_t *var2;
    sym_t *var3e[30];
    uint16_t cntParam;
    int16_t var42, tok;

    cntParam = 0;
    while ((tok = yylex()) != T_EOL) {
        if (tok == T_COMMA)
            tok = yylex();
        if (tok != G_SYM)
            syntaxErr();
        else {
            var2 = yylval.ySym;
            if (var2->sFlags & F_BPAGE)
                remSym(var2);
            else
                var2 = dupSym(var2);
            var2->sFlags = 0x2000;
            if (cntParam == 30)
                fatalErr("Too many macro parameters");
            var3e[cntParam++] = var2;
        }
    }
    if (phase != 0) {
        if (ps->sProp.vArg) {
            for (var42 = 0; var42 < ps->sProp.mArgCnt;)
                free(ps->sProp.vArg[var42++]);
            free(ps->sProp.vArg);
        }
        if (cntParam != ps->sProp.mArgCnt)
            error("Phase error in macro args");
    }
    if (cntParam) {
        ps->sProp.vArg = xalloc(cntParam * sizeof(sym_t));
    } else
        ps->sProp.vArg = 0;
    ps->sProp.mArgCnt = cntParam;
    while (cntParam--)
        ps->sProp.vArg[cntParam] = var3e[cntParam];
    skipLine();
    ps->sProp.vText = parseMacroBody();
}
/**************************************************************************
57 2dc5
**************************************************************************/
void parseMacroCall(register sym_t *ps) {
    int var2;
    char *var4;
    if (ps->sFlags & F_ARGS) {
        for (var2 = 0; var2 < ps->sProp.mArgCnt; var2++) {
            if (!(var4 = getMacroArg()))
                var4 = "";

            ps->sProp.vArg[var2]->sProp.vStr = xalloc(strlen(var4) + 1);
            strcpy(ps->sProp.vArg[var2]->sProp.vStr, var4);
            addSym(ps->sProp.vArg[var2]);
        }
        skipLine();
    }
    openMacro(ps);
}

/**************************************************************************
58 2e89 +++
 **************************************************************************/
void freeMacro(register sym_t *ps) {
    int16_t var2 = 0;
    while (var2 < ps->sProp.mArgCnt) {
        free(ps->sProp.vArg[var2]->sProp.vText);
        remSym(ps->sProp.vArg[var2]);
        var2++;
    }
}
