from airflow import DAG, Dataset
from airflow.decorators import task

from datetime import datetime

my_file = Dataset("/tmp/my_file.txt")

with DAG(
    dag_id="producer",
    schedule="@daily",
    start_date=datetime(2022,1,1),
    catchup=False,
    default_args=default_args
) as dag:
    
    @task(outlets=[my_file])
    def update_my_file():
        with open(my_file.uri, "a+") as f:
            f.write("producer update")
            
    update_my_file()