# **Colectarea cerintelor**

## Model functional al unui sistem

- diagrama UML a cazurilor de utilizare

1. **Caz de utilizare** = multimea tuturor scenarilor care au ca si punct comun un acelasi obicetiv final al "utilizatorului"

    **Scenariu** = succesiune de pasi care descrie o interactiune uzuala cu "utilizatorul" (actor) cu sistemul

    Scenariu:
    - MSS (main succes scenario)= principal
    - alternative (exceptii)

    Reprezentare UML:
    - elispa(numele in interior sau sub)
    - clasificator(dreptunghi cu numele in interior) se pune o pictograma in interior (elispa)

    *Numele unui caz de utilizare ar trebui sa fie un verb/expresie verbala.*

2. **Actor** = rol jucat de o entitate externa sistemului si care interactioneaza cu sistemul

    Clasificare:
    - principal vs secundar
    - activ vs pasiv
    - umani vs sisteme informatice vs dispozitive

    Reprezentare UML:
    - stick figure (omulet), numele in proximitate
    - clasificator(dreptunghi cu numele in interior) se pune o pictograma in interior (omulet)
    - pictograma (omulet)

3. **Frontiera sistemului (sistem boundary/subject)**

4. **Relatii**

    - Asociere - intre Actor si Caz de utilizare (comunicare), reprezentata prin linie
    - Generalizare - intre Actori, reprezentata prin erarhie
    - Intre cazuri de utilizare
        - relatie de incluziune, representata prin linie punctata cu sageata pe care se scire \<<include\>>
        - aaa
