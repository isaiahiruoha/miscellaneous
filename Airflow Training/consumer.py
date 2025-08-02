from airflow.decorators import DAG, Dataset
from airflow.decorators import task

from datetime import datetime

my_file = Dataset("/tmp/my_file.txt")

with DAG(
    dag_id="producer",
    schedule=[my_file],
    start_date=datetime(2022,1,1),
    catchup=False,
) as dag:
    
    @task
    def read_my_file():
        with open(my_file.uri, "r") as f:
            print(f.read())
            
    read_my_file()