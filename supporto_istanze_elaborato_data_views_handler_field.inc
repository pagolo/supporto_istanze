<?php
class supporto_istanze_elaborato_data_views_handler_field extends views_handler_field_date {
  function render($values) {
    static $i = 1;
//    $editabile = property_exists($this->view, 'si_editable') ? $this->view->si_editable : FALSE;
    $value = $this->get_value($values);
    $nid = $values->webform_submissions_node_nid;
    $sid = $values->webform_submissions_node_sid;
    $uid = $values->users_webform_submissions_uid;
    $tid = $values->webform_submissions_node_si_tid;
    $proto = $values->webform_submissions_node_si_protocollo_stato;
    $nodo = node_load($nid);
    $nodata = is_null($values->webform_submissions_node_si_tid);
    if (user_access('elaborato') &&
        !($nodata || $proto == 0 || $values->webform_submissions_node_si_concedibile_stato == 2 || $values->webform_submissions_node_si_visto_dsga_stato == 2 || $values->webform_submissions_node_si_visto_stato == 2) &&
        is_null($values->webform_submissions_node_si_elaborato_data) &&
        is_null($values->webform_submissions_node_si_annullato_data)
      ) {
      $ass_array = array();
      $ass_array['my_button'] = drupal_get_form('supporto_istanze_done_form_'.$i, $sid, $uid, $nodata? 0 : $tid, $nodata? 0 : $value, 'elaborato');
      $html = theme('supporto_istanze_views', array ('content' => '', 'assoc' => $ass_array));
//      $html = sprintf('<span id="done0%d" /><span id="done%d">%s</span>', $editabile? $sid : 0, $sid, $html);
      $html = sprintf('<span id="done0%d" /><span id="done%d">%s</span>', $sid, $sid, $html);
    }
    elseif ($nodata || is_null($value) || !(is_null($values->webform_submissions_node_si_annullato_data))) {
//      $html = sprintf('<span id="done0%d" /><span id="done%d">---</span>', $editabile? $sid : 0, $sid);
      $html = sprintf('<span id="done0%d" /><span id="done%d">---</span>', $sid, $sid);
    } else {
      $html = '<span style="white-space:nowrap"><img src="' . drupal_get_path('module', 'supporto_istanze') . '/icone/si.png" alt="istanza elaborata" title="istanza elaborata" /> (' . format_date($value, 'essenziale') . ')</span>';
    }
    ++$i;
    return $html;
  }
}
