/*
 * MIT License
 *
 * Copyright (c) 2019 LandF Corporation
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

//________________________________________________________________________________________
//
//  LFY-RX63N1  CMT タイマー処理
//
//----------------------------------------------------------------------------------------
//  開発履歴
//
//  2016/02/10  コーディング開始（橘）
//
//----------------------------------------------------------------------------------------
//  T.Tachibana
//  �貝&F
//________________________________________________________________________________________
//

//#include "timer.h"

#ifndef __LFY_RX63N1_CMT_TIMER__
#define __LFY_RX63N1_CMT_TIMER__

#define     CMT1_1US    6                       /*	1usec = CMT1.CLK = PCLK / 8 = 6MHz = 6count = 1usec	*/

//  間接呼び出しのプロトタイプ(引数１個)
typedef void    (*TIMER_CALL)(void);

#define     CMT0_COUNT_NUM  6000                /*	1msタイマー設定		*/
#define     CMT0_COUNT_VAL  CMT0_COUNT_NUM-1    /*	1msタイマー設定値	*/
#define     TIMER_AN    16                      /*　タイマー数			*/
//  1msec単位汎用タイマー
//int			cmt0_time[TIMER_AN];            //	ダウンカウンター
//TIMER_CALL	cmt0_call[TIMER_AN];            //	アップ後呼び出し関数
//unsigned int	freerun_timer;                  //	フリーランタイマー

#define     CMT1_COUNT_NUM  6                   /*	1usタイマー設定		*/
#define     CMT1_COUNT_VAL  CMT1_COUNT_NUM-1    /*	1usタイマー設定値	*/
//  1usec単位短期待ちタイマー
//int			cmt1_tupf;						//  タイムアップフラグ
//int			cmt1_msec;						//  msecオーダー残カウンタ
//int			cmt1_last;						//  最終カウント値
//TIMER_CALL	cmt1_call;						//  アップ後呼び出し関数

#define		ECU_TIMER_ID	0					/*	ECUタイマー(1ms)	*/
#define		TP_TIMER_ID		1					/*	分離タイマー		*/
#define		DTC_TIMER_ID	2					/*	DTC継続タイマー		*/

//________________________________________________________________________________________
//
//  cmt0_init
//----------------------------------------------------------------------------------------
//  機能説明
//      CMT0初期化
//  引数
//      無し
//  戻り
//      無し
//________________________________________________________________________________________
//
void cmt0_init(void);

//________________________________________________________________________________________
//
//  start_timer
//----------------------------------------------------------------------------------------
//  機能説明
//      指定タイマー計時開始
//  引数
//      tch         チャンネル番号
//      interval    1msec単位の待ち時間設定
//  戻り
//      無し
//________________________________________________________________________________________
//
void start_timer(int tch, int interval );

//________________________________________________________________________________________
//
//  after_call
//----------------------------------------------------------------------------------------
//  機能説明
//      指定タイマー計時開始
//  引数
//      tch         チャンネル番号
//      interval    1msec単位の待ち時間設定
//      *proc       アップ後呼び出し先
//  戻り
//      無し
//________________________________________________________________________________________
//
void after_call(int tch, int interval, void *proc );

//________________________________________________________________________________________
//
//  check_timer
//----------------------------------------------------------------------------------------
//  機能説明
//      指定タイマーアップ確認
//  引数
//      tch         チャンネル番号
//  戻り
//      int         残時間(msec)
//________________________________________________________________________________________
//
int check_timer(int tch);

//________________________________________________________________________________________
//
//  stop_timer
//----------------------------------------------------------------------------------------
//  機能説明
//      指定タイマー停止
//  引数
//      tch         チャンネル番号
//  戻り
//      無し
//________________________________________________________________________________________
//
void stop_timer(int tch);

//________________________________________________________________________________________
//
//  wait
//----------------------------------------------------------------------------------------
//  機能説明
//      指定msec間待ち
//  引数
//      msec        待ち時間
//      *loop       待ち時間中の関数呼び出し
//  戻り
//      無し
//________________________________________________________________________________________
//
void wait(int msec, void *loop);

//________________________________________________________________________________________
//
//  cmt0_job
//----------------------------------------------------------------------------------------
//  機能説明
//	  タイムアップタイマーの関数呼び出し
//  引数
//	  無し
//  戻り
//	  無し
//________________________________________________________________________________________
//
void cmt0_job(void);

//________________________________________________________________________________________
//
//  cmt0_int
//----------------------------------------------------------------------------------------
//  機能説明
//      CMT0割り込み(1msec)
//  引数
//      無し
//  戻り
//      無し
//________________________________________________________________________________________
//
//void interrupt cmt0_int(void);

//________________________________________________________________________________________
//
//  cmt1_init
//----------------------------------------------------------------------------------------
//  機能説明
//      CMT1初期化
//  引数
//      無し
//  戻り
//      無し
//________________________________________________________________________________________
//
void cmt1_init(void);

//________________________________________________________________________________________
//
//  cmt1_start
//----------------------------------------------------------------------------------------
//  機能説明
//      CMT1計時開始(1usec)
//  引数
//      count       待ち時間 0〜10000 : 10.000ms : 0.01sec
//      *proc       アップ後呼び出し先
//  戻り
//      無し
//________________________________________________________________________________________
//
void cmt1_start(int count, void *proc);

//________________________________________________________________________________________
//
//  cmt1_check
//----------------------------------------------------------------------------------------
//  機能説明
//      CMT1タイムアップ確認
//  引数
//      無し
//  戻り
//      int     0=停止中 / 1=計時中
//________________________________________________________________________________________
//
int cmt1_check(void);
int cmt1_ni_check(void);

//________________________________________________________________________________________
//
//  cmt1_stop
//----------------------------------------------------------------------------------------
//  機能説明
//	  CMT1停止と経過時間取得
//  引数
//	  無し
//  戻り
//	  経過時間(1us単位)
//________________________________________________________________________________________
//
int	cmt1_stop(void);

//________________________________________________________________________________________
//
//  cmt1_int
//----------------------------------------------------------------------------------------
//  機能説明
//      CMT1割り込み(1usec)
//  引数
//      無し
//  戻り
//      無し
//________________________________________________________________________________________
//
//void interrupt cmt1_int(void);

//________________________________________________________________________________________
//
//  swait
//----------------------------------------------------------------------------------------
//  機能説明
//      ショートウェイト    usec間待ち
//  引数
//      usec        待ち時間
//      *loop       待ち時間中の関数呼び出し
//  戻り
//      無し
//________________________________________________________________________________________
//
void swait(int usec, void *loop);

#endif  /*__LFY_RX63N1_CMT_TIMER__*/

