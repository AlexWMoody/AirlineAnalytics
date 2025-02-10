#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
Created on Wed Feb 8 14:44:33 2023
Based on: https://www.kaggle.com/datasets/arbazmohammad/world-airports-and-airlines-datasets
Sample input: --AIRLINES="airlines.yaml" --AIRPORTS="airports.yaml" --ROUTES="routes.yaml" --QUESTION="q1" --GRAPH_TYPE="bar"
@author: Alexander Moody 
@author: V00962257
"""

import yaml
import pandas as pd
import sys
import matplotlib.pyplot as plt
import numpy as np


def q_1(df_airline, df_airport, df_route, type_graph):
    #What are the top 20 airlines that offer the greatest number of routes with destination country as Canada?
    merged_df = pd.merge(df_route, df_airport, how='inner', left_on='route_to_airport_id', right_on='airport_id')
    #print(merged_df)

    merged_df = pd.merge(df_airline, merged_df, how='inner', left_on='airline_id', right_on='route_airline_id')

    merged_df = merged_df[merged_df['airport_country']=='Canada']

    answer: pd.DataFrame = merged_df.groupby(['airline_name', 'airline_icao_unique_code' ], as_index=False).size().sort_values(by='size', ascending=False)
    #print(answer, "\n")

    answer = answer.sort_values(by=['size', 'airline_name'], ascending=[False,True])
    #print(answer, "\n")

    answer = answer.head(20)
    answer['airline_name'] = answer['airline_name'] + " (" + answer['airline_icao_unique_code'] + ")"
    answer.drop(['airline_icao_unique_code'], inplace=True, axis=1)
    #print(answer, "\n")
    #format string and add to csv file plus produce graph. above correct tho.

    answer.to_csv('q1.csv', header=['subject', 'statistic'], index=False)

    answer = answer.reset_index(drop=True)
    
    if type_graph == 'bar':
        plt.rcParams.update({'font.size': 13})
        fig = answer.plot.bar(figsize=(14,11), width=0.5)
        fig.set_title('Top 20 Airlines That Offer the Most Routes With Destination Canada')
        fig.set_xticklabels(answer['airline_name'])
        fig.set_xlabel('Airline Name')
        fig.set_ylabel('Number of Appearances')
        #plt.xticks(rotation = 90)
        #fig.get_legend().remove()
        fig.legend(labels='Number of Appearances')
        fig.legend().remove()
        plt.subplots_adjust(bottom=0.35)
        #good now

    if type_graph == 'pie':
        plt.rcParams.update({'font.size': 12})
        fig = answer.plot.pie(y='size', labels=answer['airline_name'], figsize=(14,12), autopct='%1.1f%%')
        fig.set_title('Top 20 Airlines That Offer the MO\ost Routes With Destination Canada')
        #fig.set_ticklabels(answer['airport_country'])
        #.set_xlabel('Destination Country')
        #fig.set_ylabel('Number of Appearances')
        #plt.xticks(rotation = 90)
        #plt.subplots_adjust(bottom=0.25)
        fig.legend().remove()

    plt.savefig('q1.pdf', format='pdf')



def q_2(df_airport, df_route, type_graph):

    merged_df = pd.merge(df_route, df_airport, how='inner', left_on='route_to_airport_id', right_on='airport_id')
    #print(merged_df)

    answer: pd.DataFrame = merged_df.groupby(["airport_country"], as_index=False).size().sort_values(by='size', ascending=True)
    #print(answer, "\n")

    answer['airport_country'] = answer['airport_country'].str.strip()

    answer = answer.sort_values(by=['size', 'airport_country'])
    #print(answer, "\n")

    answer = answer.head(30)
    #print(answer, "\n")

    #write answer to output csv file and add graphs done! (can write without index I believe)
    answer.to_csv('q2.csv', header=['subject', 'statistic'], index=False)

    answer = answer.reset_index(drop=True)

    if type_graph == 'bar':
        plt.rcParams.update({'font.size': 13})
        fig = answer.plot.bar(figsize=(14,10), width=0.5)
        fig.set_title('Top 30 Countries With the Least Appearances as Destination Country in Routes Data')
        fig.set_xticklabels(answer['airport_country'])
        fig.set_xlabel('Destination Country')
        fig.set_ylabel('Number of Appearances')
        #plt.xticks(rotation = 90)
        #fig.get_legend().remove()
        fig.legend(labels='Number of Appearances')
        fig.legend().remove()
        plt.subplots_adjust(bottom=0.31)
        #good now
        
    if type_graph == 'pie':
        plt.rcParams.update({'font.size': 12})
        fig = answer.plot.pie(y='size', labels=answer['airport_country'], labeldistance=1.08, figsize=(12,12), autopct='%1.1f%%')
        fig.set_title('Top 30 Countries With the Least Appearances as Destination Country in Routes Data')
        fig.legend().remove()
        #plt.subplots_adjust(right=0.20)
        #fig.legend(loc='center right')
        #goodish

    plt.savefig('q2.pdf', format='pdf')


def q_3(df_airport, df_route, type_graph):
    #What are the top 10 destination airports?
    merged_df = pd.merge(df_route, df_airport, how='inner', left_on='route_to_airport_id', right_on='airport_id')
    #print(merged_df)

    answer: pd.DataFrame = merged_df.groupby(["airport_name", 'airport_icao_unique_code', 'airport_city', 'airport_country'], as_index=False).size().sort_values(by='size', ascending=False)
    #print(answer, "\n")

    answer = answer.sort_values(by=['size', 'airport_name'], ascending=[False,True])
    #print(answer, "\n")

    answer = answer.head(10)
    #print(answer, "\n")
    #format string and add to csv file plus produce graph. above correct tho.

    answer['airport_name'] = answer['airport_name'] + " (" + answer['airport_icao_unique_code'] + "), " + answer['airport_city'] + ', ' + answer['airport_country']
    answer.drop(['airport_icao_unique_code', 'airport_city', 'airport_country'], inplace=True, axis=1)

    answer.to_csv('q3.csv', header=['subject', 'statistic'], index=False)

    answer = answer.reset_index(drop=True)

    if type_graph == 'bar':
        plt.rcParams.update({'font.size': 11})
        fig = answer.plot.bar(figsize=(14,10), width=0.5)
        fig.set_title('Top 10 Destination Airports', size=18)
        fig.set_xticklabels(answer['airport_name'])
        fig.set_xlabel('Airport Name')
        fig.set_ylabel('Number of Appearances')
        plt.xticks(rotation = 82)
        #fig.get_legend().remove()
        #fig.legend(labels='Number of Appearances')
        fig.legend().remove()
        plt.subplots_adjust(bottom=0.52)
        #good now
        
    if type_graph == 'pie':
        plt.rcParams.update({'font.size': 9})
        #answer["airport_name"].str[:-1]
        fig = answer.plot.pie(y='size', labels=answer['airport_name'], labeldistance=0.7, figsize=(16,16), autopct='%1.1f%%')
        #plt.text(wrap=True)
        fig.set_title('Top 10 Destination Airports', size=18)
        fig.legend().remove()
        #plt.subplots_adjust(right=10, left = 8, bottom = 5, top=6)
        plt.subplots_adjust(right=1, left=0.001)
        #plt.subplots_adjust(left=0.45)#, left=0.2)
        #fig.legend(loc='center right')
        #goodish

    plt.savefig('q3.pdf', format='pdf')


def q_4(df_airport, df_route, type_graph):
    #What are the top 15 destination cities?
    merged_df = pd.merge(df_route, df_airport, how='inner', left_on='route_to_airport_id', right_on='airport_id')
    #print(merged_df)

    answer: pd.DataFrame = merged_df.groupby(['airport_city', 'airport_country'], as_index=False).size().sort_values(by='size', ascending=False)
    #print(answer, "\n")

    #answer['airport_name'] = answer['airport_name'].str.strip()

    answer = answer.sort_values(by=['size', 'airport_city'], ascending=[False,True])
    #print(answer, "\n")

    answer = answer.head(15)
    #print(answer, "\n")
    #format string and add to csv file plus produce graph. above correct tho.

    answer['airport_city'] = answer['airport_city'] + ', ' + answer['airport_country'] 
    answer.drop(['airport_country'], inplace=True, axis=1)

    answer.to_csv('q4.csv', header=['subject', 'statistic'], index=False)

    answer = answer.reset_index(drop=True)

    if type_graph == 'bar':
        plt.rcParams.update({'font.size': 13})
        fig = answer.plot.bar(figsize=(14,10), width=0.5)
        fig.set_title('Top 15 Destination Cities', size=18)
        fig.set_xticklabels(answer['airport_city'])
        fig.set_xlabel('Airport City')
        fig.set_ylabel('Number of Appearances')
        #plt.xticks(rotation = 80)
        #fig.get_legend().remove()
        #fig.legend(labels='Number of Appearances')
        fig.legend().remove()
        plt.subplots_adjust(bottom=0.41)
        #good now
        
    if type_graph == 'pie':
        plt.rcParams.update({'font.size': 14})
        fig = answer.plot.pie(y='size', labels=answer['airport_city'], labeldistance=1.05, figsize=(16,16), autopct='%1.1f%%')
        fig.set_title('Top 15 Destination Cities', size=18)
        fig.legend().remove()
        #plt.subplots_adjust(right=10, left = 8, bottom = 5, top=6)
        plt.subplots_adjust(right=0.8, left=0.2)
        #fig.legend(loc='center right')
        #goodish

    plt.savefig('q4.pdf', format='pdf')


def q_5(df_airline, df_airport, df_route, type_graph):
   # What are the unique top 10 Canadian routes (i.e., if CYYJ-CYVR is included, CYVR-CYYJ should not) with most difference between the destination altitude and the origin altitude?
    #merged_df = pd.merge(df_airport, df_route, how='inner', left_on='airport_country', right_on='route_from_aiport_id')
    merged_df = pd.merge(df_route, df_airport, how='inner', left_on='route_from_aiport_id', right_on='airport_id')
    print(merged_df, '\n')

    merged_df2 = pd.merge(df_route, df_airport, how='inner', left_on='route_to_airport_id', right_on='airport_id')
    print(merged_df2, '\n')

    #merged_df = merged_df[merged_df['airport_country']=='Canada']
    #print(merged_df, '\n')

    answer: pd.DataFrame = merged_df.groupby(['route_from_aiport_id', 'airport_id', 'airport_icao_unique_code', 'airport_country', 'airport_altitude', 'route_to_airport_id'], as_index=False).size().sort_values(by='size', ascending=False)
    print(answer, '\n')

    answer2: pd.DataFrame = merged_df2.groupby(['route_to_airport_id', 'airport_id', 'airport_icao_unique_code', 'airport_country', 'airport_altitude'], as_index=False).size().sort_values(by='size', ascending=False)
    print(answer2, '\n')

    answerf = pd.merge(answer, answer2, how='inner', left_on='route_to_airport_id', right_on='route_to_airport_id')
    print(answerf, '\n')

    answerf = answerf[answerf['airport_country_x']=='Canada']
    answerf = answerf[answerf['airport_country_y']=='Canada']
    #answer2 = answer2[answer2['airport_country']=='Canada']
    print(answerf, '\n')
    #print(answer2, '\n')

    #print(df_airport,'\n')
    #print(df_route,'\n')

    #answer = pd.merge(df_airport, merged_df, how='inner', left_on='airport_altitude', right_on='route_airline_id')
    #print(answer, '\n')

    #answer: pd.DataFrame = merged_df.groupby(['airport_country', 'airport_icao_unique_code', 'airport_altitude'], as_index=False).size().sort_values(by='size', ascending=False)
    #print(answer, '\n')

    #answer: pd.DataFrame = merged_df.groupby(['airport_city', 'airport_country'], as_index=False).size().sort_values(by='size', ascending=False)

    #answer = answer.sort_values(by=['size', 'airport_city'], ascending=[False,True])
    #print(answer, "\n")

    #answer = answer.head(10)

def main():
    """Main entry point of the program."""
    # calling the sample function

    #get command line arguments/files
    if(len(sys.argv) >= 1): #6?? maybe something more open?
        prog_name = sys.argv[0][2:]
        airline_file = sys.argv[1][11:]
        airport_file = sys.argv[2][11:]
        route_file = sys.argv[3][9:]
        question_number = sys.argv[4][11:]
        type_graph = sys.argv[5][13:]

    #print(airport_file)

    #https://pandashowto.com/how-to-convert-yaml-to-pandas-dataframe/
    """with open('airlines.yaml', 'r') as file_airline:
        airline_data = yaml.load(file_airline, Loader=yaml.FullLoader)
    df_airline = pd.DataFrame(airline_data['airlines'])"""
    
    with open(airline_file, 'r') as file_airline:
        airline_data = yaml.load(file_airline, Loader=yaml.FullLoader)
    df_airline = pd.DataFrame(airline_data['airlines'])

    with open(airport_file, 'r') as file_airport:
        airport_data = yaml.load(file_airport, Loader=yaml.FullLoader)
    df_airport = pd.DataFrame(airport_data['airports'])

    with open(route_file, 'r') as file_route:
        route_data = yaml.load(file_route, Loader=yaml.FullLoader)
    df_route = pd.DataFrame(route_data['routes'])

    #add if statemetns to call each function based on question

    if question_number == "q1":
        q_1(df_airline, df_airport, df_route, type_graph)

    if question_number == "q2":
        q_2(df_airport, df_route, type_graph)

    if question_number == "q3":
        q_3(df_airport, df_route, type_graph)

    if question_number == "q4":
        q_4(df_airport, df_route, type_graph)

    if question_number == "q5":
        q_5(df_airline, df_airport, df_route, type_graph)



if __name__ == '__main__':
    main()
