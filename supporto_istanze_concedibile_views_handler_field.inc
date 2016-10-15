<?php
class supporto_istanze_concedibile_views_handler_field extends views_handler_field {
  function render($values) {
//    $editabile = ($this->view->name != 'le_mie_istanze' && !($this->view->name == 'istanze_personale' && $this->view->current_display == 'page_1'));
    $editabile = property_exists($this->view, 'si_editable') ? $this->view->si_editable : FALSE;
    $value = $this->get_value($values);
    $sid = $values->webform_submissions_node_sid;
    $nid = $values->webform_submissions_node_nid;
    $tid = $values->webform_submissions_node_si_tid;
    $protoc = $values->webform_submissions_node_si_protocollo_stato;
    $visto_dsga = property_exists($values, 'webform_submissions_node_si_visto_dsga_stato') ? $values->webform_submissions_node_si_visto_dsga_stato : NULL;
    $visto_referente = property_exists($values, 'webform_submissions_node_si_visto_referente_stato') ? $values->webform_submissions_node_si_visto_referente_stato : NULL;
    $visto = $values->webform_submissions_node_si_visto_stato;
    $usa_visto_dsga = $usa_visto_referente = FALSE;
    $acquisisci = FALSE;
    $nodo = node_load($nid);
    if (isset($nodo->field_si_dsga['und'][0]['value']) && $nodo->field_si_dsga['und'][0]['value'] == 1) {
      $usa_visto_dsga = TRUE;
    }
    if (isset($nodo->field_si_referente['und'][0]['value']) && $nodo->field_si_referente['und'][0]['value'] == 1) {
      $usa_visto_referente = TRUE;
    }
    if (isset($nodo->field_si_acquisisci['und'][0]['value']) && $nodo->field_si_acquisisci['und'][0]['value'] == 1) {
      $acquisisci = TRUE;
    }
    $nodata = is_null($tid);
    //drupal_set_message($visto_referente."!");
    if (user_access('acquisito') && $editabile && !$nodata && $protoc == 1 && is_null($visto) && (!$usa_visto_dsga || is_null($visto_dsga))) {
      $status = 'da valutare';
      switch ($value) {
        case 1:
          $status = $acquisisci? 'acquisito' : 'concedibile';
          break;
        case 2:
          $status = $acquisisci? 'non acquisito' : 'non concedibile';
          break;            
      }
      $a = drupal_get_destination();
      $html = sprintf('<span id="sid%d"><a title=\'clic qui per valutare o modificare\' href=\'node/%d/submission/%d/istanza_%s/%d?destination=%s\'>%s</a></span>', $sid, $nid, $sid, $acquisisci? 'acquisisci' : 'concedi', $tid, $a['destination'], $status);
    }
    elseif ($nodata || $value == 0) {
      $html = sprintf('<span id="sid%d">---</span>', $sid);
    } else {
      $si_no = ($value == 1 ? 'si' : 'no');
      $msg = ($value == 2? 'non ' : '') . ($acquisisci? 'acquisito' : 'concedibile');
      $html = '<img src="' . drupal_get_path('module', 'supporto_istanze') . '/icone/' . $si_no . '.png" alt="' . $msg . '" title="' . $msg . '" />';
    }
    return $html;
  }
}
