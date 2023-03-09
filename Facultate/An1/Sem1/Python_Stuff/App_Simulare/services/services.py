#
class NoSirFoundError(Exception):
    pass

class services_pictura:
    #servicesul pentru pictura
    def __init__(self,repo):
        #initializare
        self.__repo=repo
    
    def get_all_nume_sort_an(self,sir):
        #retureaza obicete de tip pictura care includ sir 'sir' in numele autorului si sunt sortate dupa an descrescator
        all=self.__repo.get_all_pictura()
        rezultat=[]
        for pic in all:
            if sir in pic.get_nume():
                rezultat.append(pic)

        if not rezultat:
            raise NoSirFoundError

        rezultat.sort(reverse=True, key=lambda el: el.get_an())
        return rezultat
    
    def get_picture_an_by_autor(self, autor):
        #returneaza anii tuturor picturilor autorului
        all=self.__repo.get_all_pictura()
        rezultat=[]
        for pic in all:
            if pic.get_nume_autor()==autor:
                rezultat.append(pic.get_an())
        return rezultat
    
    def get_cel_mai_recent(self):
        #returenza o lista de  liste in care sunt autorul si cea mai recenta pictura a lui
        all=self.__repo.get_all_pictura()
        rezultat=[]
        for pic in all:
            if pic.get_nume_autor() not in (row[0] for row in rezultat):
                l=self.get_picture_an_by_autor(pic.get_nume_autor())
                l.sort(reverse=True)
                rezultat.append([pic.get_nume_autor(),l[0]])
        return rezultat
            




