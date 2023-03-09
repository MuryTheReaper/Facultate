#main
from repository.repo import repo_pictura
from services.services import services_pictura
from tests.test_domain import test_pictura
from tests.test_repo import test_repo
from tests.test_serv import test_get_all_nume_sort_an
from ui.console import console

try:
    repo=repo_pictura("data/pictures.txt")
    serv=services_pictura(repo)
    ui=console(serv)
    ui.show_ui()
except ValueError:
    print("Date gresit in fisier")